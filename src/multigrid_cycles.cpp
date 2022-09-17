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


void full_restriction(Grid &a, Grid &x, Grid &b, Grid &residual, Grid &error,
    const int num_iterations, const int initial_depth) {

    // Set initial depth for grids
    x.depth = initial_depth;

    // Presmooth x at initial depth
    sor_smooth(a, x, b, num_iterations);

    // Find the current residual
    Grid temp = Grid(x);
    multiply(a, x, temp);
    subtract(b, temp, residual);

    // Restrict residual (and LHS matrix)
    x.depth++;
    restrict_vector(residual);
    restrict_matrix(a);

    // Restrict down to coarsest grid
    for (auto depth = a.depth; depth < x.max_depth() - 1; depth++) {
        // Presmooth x at finer level
        sor_smooth(a, error, residual, num_iterations);

        // Find the current residual
        multiply(a, error, temp);
        subtract(residual, temp, residual);

        // Restrict residual (and LHS matrix)
        x.depth++;
        restrict_vector(residual);
        restrict_matrix(a);
    }

    // Further smooth on coarsest grid
    x.depth--;
    sor_smooth(a, error, residual, num_iterations);
}


void full_interpolation(Grid &a, Grid &x, Grid &b, Grid &residual, Grid &error,
    const int num_iterations, const int initial_depth) {

    // Interpolate up to second-finest mesh
    for (auto depth = x.max_depth(); depth > 1; depth--) {
        // Map the correction from the coarse grid to a finer grid
        x.depth--;
        interpolate_vector(error);

        // Apply a post-smoother to Ax=b
        interpolate_matrix(a);
        sor_smooth(a, error, residual, num_iterations);
    }

    // Map the correction from the second finest grid to the finest grid
    x.depth--;
    interpolate_vector(error);
    add(x, error, x);

    // Apply a post-smoother to Ax=b
    interpolate_matrix(a);
    sor_smooth(a, x, b, 0, num_iterations);
}


void v_cycle(Grid &a, Grid &x, Grid &b, Grid &residual, Grid &error,
    const int num_iterations, const int initial_depth) {
    
    // Restrict and smooth all the way down to coarsest grid depth
    full_restriction(a, x, b, residual, error, num_iterations, initial_depth);
    // Interpolate and smooth all the way up to finest grid depth
    full_interpolation(a, x, b, residual, error, num_iterations, initial_depth);
}


void w_cycle(Grid &a, Grid &x, Grid &b, Grid &residual, Grid &error,
    const int num_iterations){

    // Restrict and smooth all the way down to coarsest grid depth
    full_restriction(a, x, b, residual, error, num_iterations, 0);

    // Interpolate everything once to start V-cycles
    x.depth--;
    interpolate_vector(error);
    interpolate_vector(residual);
    interpolate_matrix(a);

    // V-cycle repeatedly at varying depths to form the W-cycle
    const auto num_intermediate_cycles = std::pow(2, x.max_depth()) - 1;
    for (auto i = 0; i < num_intermediate_cycles; i++) {
        v_cycle(a, x, b, residual, error, num_iterations, w_cycle_intermediate_depths[i] + 1);
    }
    
    // Restrict everything once to end V-cycles
    x.depth++;
    restrict_vector(error);
    restrict_vector(residual);
    restrict_matrix(a);

    // Interpolate and smooth all the way up to finest grid depth
    full_interpolation(a, x, b, residual, error, num_iterations, 0);
}
