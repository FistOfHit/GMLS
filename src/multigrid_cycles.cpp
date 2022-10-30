#include "../include/multigrid_cycles.h"

#include "../include/arithmetic.h"
#include "../include/grid.h"
#include "../include/reshapers.h"
#include "../include/smoothers.h"

#include <iostream>


void restrict(Grid &a, Grid &x, Grid &b, Grid &residual, Grid &error,
    const int num_iterations, const int final_depth) {

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
    for (auto _ = x.depth; _ < final_depth; _++) {
        // Presmooth x at finer level
        sor_smooth(a, error, residual, num_iterations);

        // Find the current residual
        multiply(a, error, temp);
        subtract(residual, temp, residual);

        // Restrict residual (and LHS matrix)
        restrict_vector(residual);
        restrict_matrix(a);
        x.depth++;
    }

    // Further smooth on coarsest grid
    sor_smooth(a, error, residual, num_iterations);
}


void interpolate(Grid &a, Grid &x, Grid &b, Grid &residual, Grid &error,
    const int num_iterations, const int final_depth) {

    // TODO: check or enforce that initial depth is actually what is given?

    // Interpolate up to second-finest mesh
    for (auto _ = x.depth; _ > final_depth + 1; _--) {
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
    const int num_iterations, const int final_depth) {

    // Restrict and smooth all the way down to coarsest grid depth
    restrict(a, x, b, residual, error, num_iterations, x.max_depth());

    // Interpolate and smooth all the way up to final grid depth
    interpolate(a, x, b, residual, error, num_iterations, final_depth);
}


void w_cycle(Grid &a, Grid &x, Grid &b, Grid &residual, Grid &error,
    const int num_iterations) {

    // V-cycle repeatedly at varying depths to form the W-cycle.
    // __builtin_ctz used to generate depths for the W-cycle pattern.
    for (auto i = 2; i < std::pow(2, x.max_depth()+1); i += 2) {
        v_cycle(a, x, b, residual, error, num_iterations,
            x.max_depth() - __builtin_ctz(i));
    }
    
    // Restrict everything once and interpolate back to top to end V-cycles
    restrict_vector(error);
    restrict_vector(residual);
    restrict_matrix(a);
    x.depth++;

    interpolate(a, x, b, residual, error, num_iterations, 0);
}
