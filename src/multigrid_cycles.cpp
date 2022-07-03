#include "../includes/src_includes/arithmetic.h"
#include "../includes/src_includes/multigrid_cycles.h"
#include "../includes/src_includes/reshapers.h"
#include "../includes/src_includes/smoothers.h"
#include <map>
#include <memory>
#include <vector>


using grid_list = std::map<int, std::vector<float>>;


// void w_cycle(grid_list a_grids, grid_list x_grids, grid_list b_grids) {

//     return;
// };


void v_cycle(grid_list a_grids, grid_list x_grids, grid_list b_grids, grid_list r_grids, grid_list temp_grids, const int num_iterations) {
    /* Perform one V-cycle iteration on a series of grids.


    */

    // Restrict down to coarsest mesh
    for (auto i = 0; i < a_grids.size() - 1; i++) {
        // Presmooth x_fine
        sor_smoother(a_grids[i], x_grids[i], b_grids[i], num_iterations);

        // Find residual_fine
        multiply(a_grids[i], x_grids[i], temp_grids[i]);
        subtract(b_grids[i], temp_grids[i], r_grids[i]);

        // Restrict residual_fine to residual_coarse
        restrict_vector(r_grids[i], r_grids[i+1]);

        // Solve on coarser meshes A_coarse x_coarse = r_coarse
        sor_smoother(a_grids[i+1], x_grids[i+1], b_grids[i+1], num_iterations);
    }

    // Interpolate up to finest mesh
    for (auto i = a_grids.size() - 1; i > 0; i++) {
        // Map the correction from the coarse grid we just found to upper level
        interpolate_vector(x_grids[i+1], x_grids[i]);
        add(x_grids[i], r_grids[i], x_grids[i]); //?? confirm

        // Apply a post-smoother to A_fine x_fine = b_fine, getting a more accurate x_fine
        sor_smoother(a_grids[i], x_grids[i], b_grids[i], num_iterations);
    }
};