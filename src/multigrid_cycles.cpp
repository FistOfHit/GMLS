#include "../includes/src_includes/arithmetic.h"
#include "../includes/src_includes/multigrid_cycles.h"
#include "../includes/src_includes/reshapers.h"
#include "../includes/src_includes/smoothers.h"
#include <map>
#include <memory>
#include <vector>


using vector = std::vector<float>;


void v_cycle(vector &a, vector &x, vector &b, vector &r, const int num_grids,
    const int num_iterations, const int num_cycles) {
    /* Perform one V-cycle iteration on a series of grids.

    Notes
    -----

    Parameters
    ----------
    */

    // Get dimensions of A from x and b
    const int num_rows = x.size();
    const int num_cols = b.size();

    // Restrict down to coarsest mesh
    vector temp = vector(x);
    for (auto grid_depth = 0; grid_depth < num_grids - 1; grid_depth++) {
        // Presmooth x at finer level
        sor_smooth(a, x, b, grid_depth, num_iterations);

        // Find the current residual
        multiply(a, num_rows, num_cols, x, grid_depth, temp);
        subtract(b, temp, grid_depth, r);

        // Restrict residual_fine to residual_coarse
        restrict_vector(r, grid_depth);

        // Solve on coarser meshes Ax=r
        sor_smooth(a, x, r, grid_depth + 1, num_iterations);
    }

    // Interpolate up to finest mesh
    for (auto grid_depth = num_grids; grid_depth >= 0; grid_depth--) {
        // Map the correction from the coarse grid we just found to a finer mesh
        interpolate_vector(x, grid_depth);
        add(x, r, grid_depth, x); //?? confirm

        // Apply a post-smoother to Ax=b
        sor_smooth(a, x, b, grid_depth, num_iterations);
    }
};

// void w_cycle(vector a, vector x, vector b, vector r, const int num_grids, const int num_iterations, const int num_cycles) {}
