#include "../include/multigrid_cycles.h"

#include "../include/arithmetic.h"
#include "../include/grid.h"
#include "../include/reshapers.h"
#include "../include/smoothers.h"

#include <cmath>
#include <map>
#include <memory>
#include <vector>
#include <iostream>


using vector = std::vector<float>;


// Pre-determined depths for intermediate V-cycles to form the "W" in W-cycle
static std::vector<int> w_cycle_intermediate_depths = std::vector<int>{
    1, 2, 1,
    3, 1, 2, 1,
    4, 1, 2, 1, 3, 1, 2, 1,
    5, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1,
};


void v_cycle(Grid &a, Grid &x, Grid &b, Grid &residual, Grid &error,
    const int num_iterations) {

    // Presmooth x at finest level
    sor_smooth(a, x, b, num_iterations);

    // Find the current residual
    Grid temp = Grid(x);
    multiply(a, x, temp);
    subtract(b, temp, residual);

    // Restrict residual (and LHS matrix)
    restrict_vector(residual);
    restrict_matrix(a);

    // Restrict down to coarsest grid
    for (auto depth = 1; depth < x.max_depth() - 1; depth++) {
        // Presmooth x at finer level
        sor_smooth(a, error, residual, num_iterations);

        // Find the current residual
        multiply(a, error, temp);
        subtract(residual, temp, residual);

        // Restrict residual (and LHS matrix)
        restrict_vector(residual);
        restrict_matrix(a);
    }

    // Further smooth on coarsest grid
    a.depth -= 1;
    error.depth -= 1;
    residual.depth -= 1;
    sor_smooth(a, error, residual, num_iterations);

    // Interpolate up to second-finest mesh
    for (auto depth = x.max_depth() - 1; depth > 2; depth--) {
        // Map the correction from the coarse grid to a finer grid
        interpolate_vector(error);

        // Apply a post-smoother to Ax=b
        interpolate_matrix(a);
        sor_smooth(a, error, residual, num_iterations);
    }

    // Map the correction from the second finest to finest grid
    interpolate_vector(error);
    add(x, error, x);

    // Apply a post-smoother to Ax=b
    interpolate_matrix(a);
    sor_smooth(a, x, b, 0, num_iterations);
}


void w_cycle(Grid &a, Grid &x, Grid &b, Grid &residual, Grid &error,
    const int num_iterations){

    // Presmooth x at finest level
    sor_smooth(a, x, b, num_iterations);

    // Find the current residual
    Grid temp = Grid(x);
    multiply(a, x, temp);
    subtract(b, temp, residual);

    // Restrict residual (and LHS matrix)
    restrict_vector(residual);
    restrict_matrix(a);

    // Restrict down to coarsest grid
    for (auto grid_depth = 1; grid_depth < x.max_depth() - 1; grid_depth++) {
        // Presmooth x at finer level
        sor_smooth(a, error, residual, grid_depth, num_iterations);

        // Find the current residual
        multiply(a, error, temp);
        subtract(residual, temp, residual);

        // Restrict residual (and LHS matrix)
        restrict_vector(residual);
        restrict_matrix(a);
    }

    // Further smooth on coarsest grid
    sor_smooth(a, error, residual, x.max_depth() - 1, num_iterations);

    // Interpolate everything once to start V-cycles
    a.depth -= 1;
    error.depth -= 1;
    residual.depth -= 1;
    interpolate_vector(error);
    interpolate_vector(residual);
    interpolate_matrix(a);

    // V-cycle repeatedly at varying depths to form the W-cycle
    const auto num_intermediate_cycles = std::pow(2, x.max_depth()) - 1;
    for (auto i = 0; i < num_intermediate_cycles; i++) {
        v_cycle(a, x, b, residual, error, w_cycle_intermediate_depths[i] + 1, num_iterations);
    }
    
    // Restrict everything once to end V-cycles
    restrict_vector(error, x.max_depth() - 2);
    restrict_vector(residual, x.max_depth() - 2);
    restrict_matrix(a, x.max_depth() - 2);

    // Interpolate up to second-finest mesh
    for (auto grid_depth = x.max_depth() - 1; grid_depth > 2; grid_depth--) {
        // Map the correction from the coarse grid to a finer grid
        interpolate_vector(error);

        // Apply a post-smoother to Ax=b
        interpolate_matrix(a);
        sor_smooth(a, error, residual, num_iterations);
    }

    // Map the correction from the second finest to finest grid
    interpolate_vector(error, 1);
    add(x, error, x);

    // Apply a post-smoother to Ax=b
    interpolate_matrix(a);
    sor_smooth(a, x, b, num_iterations);
}
