#include "../include/arithmetic.h"
#include "../include/multigrid_cycles.h"
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


void v_cycle(vector &a, vector &x, vector &b, vector &residual, vector&error,
    const int num_grids, const int num_iterations) {

    // Presmooth x at finest level
    sor_smooth(a, x, b, 0, num_iterations);

    // Find the current residual
    vector temp = vector(x);
    multiply(a, x, 0, temp);
    subtract(b, temp, 0, residual);

    // Restrict residual (and LHS matrix)
    restrict_vector(residual, 0);
    restrict_matrix(a, 0);

    // Restrict down to coarsest grid
    for (auto grid_depth = 1; grid_depth < num_grids - 1; grid_depth++) {
        // Presmooth x at finer level
        sor_smooth(a, error, residual, grid_depth, num_iterations);

        // Find the current residual
        multiply(a, error, grid_depth, temp);
        subtract(residual, temp, grid_depth, residual);

        // Restrict residual (and LHS matrix)
        restrict_vector(residual, grid_depth);
        restrict_matrix(a, grid_depth);
    }

    // Further smooth on coarsest grid
    sor_smooth(a, error, residual, num_grids - 1, num_iterations);

    // Interpolate up to second-finest mesh
    for (auto grid_depth = num_grids - 1; grid_depth > 2; grid_depth--) {
        // Map the correction from the coarse grid to a finer grid
        interpolate_vector(error, grid_depth);

        // Apply a post-smoother to Ax=b
        interpolate_matrix(a, grid_depth);
        sor_smooth(a, error, residual, grid_depth, num_iterations);
    }

    // Map the correction from the second finest to finest grid
    interpolate_vector(error, 1);
    add(x, error, 0, x);

    // Apply a post-smoother to Ax=b
    interpolate_matrix(a, 1);
    sor_smooth(a, x, b, 0, num_iterations);
}


void w_cycle(vector &a, vector &x, vector &b, vector &residual, vector&error, 
    const int num_grids, const int num_iterations) {

    // Presmooth x at finest level
    sor_smooth(a, x, b, 0, num_iterations);

    // Find the current residual
    vector temp = vector(x);
    multiply(a, x, 0, temp);
    subtract(b, temp, 0, residual);

    // Restrict residual (and LHS matrix)
    restrict_vector(residual, 0);
    restrict_matrix(a, 0);

    // Restrict down to coarsest grid
    for (auto grid_depth = 1; grid_depth < num_grids - 1; grid_depth++) {
        // Presmooth x at finer level
        sor_smooth(a, error, residual, grid_depth, num_iterations);

        // Find the current residual
        multiply(a, error, grid_depth, temp);
        subtract(residual, temp, grid_depth, residual);

        // Restrict residual (and LHS matrix)
        restrict_vector(residual, grid_depth);
        restrict_matrix(a, grid_depth);
    }

    // Further smooth on coarsest grid
    sor_smooth(a, error, residual, num_grids - 1, num_iterations);

    // Interpolate everything once to start V-cycles
    interpolate_vector(error, num_grids - 1);
    interpolate_vector(residual, num_grids - 1);
    interpolate_matrix(a, num_grids - 1);

    // V-cycle repeatedly at varying depths to form the W-cycle
    const auto num_intermediate_cycles = std::pow(2, num_grids) - 1;
    for (auto i = 0; i < num_intermediate_cycles; i++) {
        v_cycle(a, x, b, residual, error, w_cycle_intermediate_depths[i] + 1, num_iterations);
    }
    
    // Restrict everything once to end V-cycles
    restrict_vector(error, num_grids - 2);
    restrict_vector(residual, num_grids - 2);
    restrict_matrix(a, num_grids - 2);

    // Interpolate up to second-finest mesh
    for (auto grid_depth = num_grids - 1; grid_depth > 2; grid_depth--) {
        // Map the correction from the coarse grid to a finer grid
        interpolate_vector(error, grid_depth);

        // Apply a post-smoother to Ax=b
        interpolate_matrix(a, grid_depth);
        sor_smooth(a, error, residual, grid_depth, num_iterations);
    }

    // Map the correction from the second finest to finest grid
    interpolate_vector(error, 1);
    add(x, error, 0, x);

    // Apply a post-smoother to Ax=b
    interpolate_matrix(a, 1);
    sor_smooth(a, x, b, 0, num_iterations);
}
