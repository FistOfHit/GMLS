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


void restrict(Grid &a, Grid &x, Grid &b, Grid &residual, Grid &error,
    const int num_iterations, const int initial_depth, const int final_depth) {

    // Set initial depth for grids
    x.depth = initial_depth;
    std::cout << x.depth;

    // Presmooth x at initial depth
    sor_smooth(a, x, b, num_iterations);

    // Find the current residual
    Grid temp = x;
    multiply(a, x, temp);
    subtract(b, temp, residual);

    // Restrict residual (and LHS matrix)
    restrict_vector(residual);
    restrict_matrix(a);
    x.depth++;

    // Restrict down to coarsest grid
    for (auto depth = x.depth; depth < final_depth - 1; depth++) {
        // Presmooth x at finer level
        sor_smooth(a, error, residual, num_iterations);

        // Find the current residual
        multiply(a, error, temp);
        subtract(residual, temp, residual);

        // Restrict residual (and LHS matrix)
        restrict_vector(residual);
        restrict_matrix(a);
        x.depth++;
        std::cout << "restricting once";
    }

    // Further smooth on coarsest grid
    sor_smooth(a, error, residual, num_iterations);
    x.depth++;
    std::cout << x.depth;
}


void interpolate(Grid &a, Grid &x, Grid &b, Grid &residual, Grid &error,
    const int num_iterations, const int initial_depth, const int final_depth) {

    // TODO: check or enforce that initial depth is actually what is given?

    // Interpolate up to second-finest mesh
    for (auto depth = initial_depth; depth > final_depth + 1; depth--) {
        // Map the correction from the coarse grid to a finer grid
        interpolate_vector(error);

        // Apply a post-smoother to Ax=b
        interpolate_matrix(a);
        sor_smooth(a, error, residual, num_iterations);
        x.depth--;
    }

    // Map the correction from the second finest grid to the finest grid
    interpolate_vector(error);
    add(x, error, x);

    // Apply a post-smoother to Ax=b
    interpolate_matrix(a);
    sor_smooth(a, x, b, 0, num_iterations);
    x.depth--;
}


void v_cycle(Grid &a, Grid &x, Grid &b, Grid &residual, Grid &error,
    const int num_iterations, const int minimum_depth, const int maximum_depth) {
    
    // Restrict and smooth all the way down to coarsest grid depth
    restrict(a, x, b, residual, error, num_iterations, minimum_depth, maximum_depth);
    std::cout << x.depth;
    // Interpolate and smooth all the way up to finest grid depth
    interpolate(a, x, b, residual, error, num_iterations, maximum_depth, minimum_depth);
    std::cout << x.depth;
}


void w_cycle(Grid &a, Grid &x, Grid &b, Grid &residual, Grid &error,
    const int num_iterations) {

    // Restrict and smooth all the way down to coarsest grid depth
    restrict(a, x, b, residual, error, num_iterations, 0, x.max_depth());

    // Interpolate everything once to start V-cycles
    interpolate_vector(error);
    interpolate_vector(residual);
    interpolate_matrix(a);
    x.depth--;

    // V-cycle repeatedly at varying depths to form the W-cycle
    const auto num_intermediate_cycles = std::pow(2, x.max_depth()-1) - 1;
    for (auto i = 0; i < num_intermediate_cycles - 1; i++) {
        v_cycle(a, x, b, residual, error, num_iterations,
            x.max_depth() - w_cycle_intermediate_depths[i],
            x.max_depth() - w_cycle_intermediate_depths[i+1]);
    }
    
    // Restrict everything once to end V-cycles
    restrict_vector(error);
    restrict_vector(residual);
    restrict_matrix(a);
    x.depth++;

    // Interpolate and smooth all the way up to finest grid depth
    interpolate(a, x, b, residual, error, num_iterations, x.max_depth(), 0);
}
