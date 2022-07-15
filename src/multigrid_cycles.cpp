#include "../includes/src_includes/arithmetic.h"
#include "../includes/src_includes/multigrid_cycles.h"
#include "../includes/src_includes/reshapers.h"
#include "../includes/src_includes/smoothers.h"
#include <math.h>
#include <map>
#include <memory>
#include <vector>


using vector = std::vector<float>;


void v_cycle(vector &a, vector &x, vector &b, vector &r, vector&e, 
    const int num_grids, const int num_iterations) {
    /* Perform one V-cycle iteration on a series of grids.

    Notes
    -----

    Parameters
    ----------
    */

    // Get dimensions of A from x and b
    const auto num_rows = x.size();
    const auto num_cols = b.size();

    // Restrict down to coarsest mesh
    vector temp = vector(x);
    for (auto grid_depth = 0; grid_depth < num_grids - 1; grid_depth++) {
        // Presmooth x at finer level
        sor_smooth(a, x, b, grid_depth, num_iterations);

        // Find the current residual
        multiply(a, num_rows, num_cols, x, grid_depth, temp);
        subtract(b, temp, grid_depth, r);

        // Restrict residual (and LHS matrix)
        restrict_vector(r, grid_depth);
        restrict_matrix(a, grid_depth);

        // Solve on coarser meshes Ae=r
        sor_smooth(a, e, r, grid_depth + 1, num_iterations);
    }

    // Interpolate up to finest mesh
    for (auto grid_depth = num_grids; grid_depth >= 0; grid_depth--) {
        // Map the correction from the coarse grid we just found to a finer mesh
        interpolate_vector(e, grid_depth);
        add(x, e, grid_depth, x);

        // Apply a post-smoother to Ax=b
        sor_smooth(a, x, b, grid_depth, num_iterations);
    }
}

void w_cycle(vector &a, vector &x, vector &b, vector &r, vector&e, 
    const int num_grids, const int num_iterations) {
        /* Perform one W-cycle iteration on a series of grids.

    Notes
    -----

    Parameters
    ----------
    */

    // Get dimensions of A from x and b
    const auto num_rows = x.size();
    const auto num_cols = b.size();

    // Restrict down to coarsest mesh
    vector temp = vector(x);
    for (auto grid_depth = 0; grid_depth < num_grids - 1; grid_depth++) {
        // Presmooth x at finer level
        sor_smooth(a, x, b, grid_depth, num_iterations);

        // Find the current residual
        multiply(a, num_rows, num_cols, x, grid_depth, temp);
        subtract(b, temp, grid_depth, r);

        // Restrict residual (and LHS matrix)
        restrict_vector(r, grid_depth);
        restrict_matrix(a, grid_depth);

        // Solve on coarser meshes Ae=r
        sor_smooth(a, e, r, grid_depth + 1, num_iterations);
    }

    const auto num_intermediate_cycles = std::pow(2, num_grids) - 1;
    


    // Interpolate up to finest mesh
    for (auto grid_depth = num_grids; grid_depth >= 0; grid_depth--) {
        // Interpolate the error and use it to correct x
        interpolate_vector(e, grid_depth);
        add(x, e, grid_depth, x);

        // Apply a post-smoother to Ax=b
        sor_smooth(a, x, b, grid_depth, num_iterations);
    }
}
