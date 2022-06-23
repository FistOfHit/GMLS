#include <map>
#include <memory>
#include <vector>

#include "../includes/src_includes/interpolation.h"
#include "../includes/src_includes/multigrid_cycles.h"
#include "../includes/src_includes/smoother.h"
#include "../includes/src_includes/restriction.h"


using grid_list = std::map<int, std::vector<float>>;
using grid_size_list = std::map<int, std::pair<size_t, size_t>>;


// void w_cycle(grid_list a_grids, grid_list x_grids, grid_list b_grids) {

//     return;
// };


void v_cycle(grid_list a_grids, grid_list x_grids, grid_list b_grids, grid_list r_grids) {

    // Presmooth solution at finest level
    sor_smoother(a_grids.find(0)->second, x_grids.find(0)->second, b_grids.find(0)->second, 10);

    // Find residual
    std::vector<float> res;
    r_grids[0] = b_grids[0] - a_grids[0] * x_grids[0];

    // Restrict residual to next level
    restrict_vector(r_grids[1]);

    // Solve on coarser meshes A1x1 = r1
    if (a_grids.size() == 2) {
        sor_smoother(a_grids.find(1)->second, x_grids.find(1)->second, b_grids.find(1)->second);
    } else {
        v_cycle(a_grids[1], x_grids[1], b_grids[1]);
    }

    // Map the correction from the coarse grid we just found to upper leve
    x_grids[0] = x_grids[0] + interpolate_vector(x_grids[1]);

    // Apply a post-smoother to A0x0 = b0, getting a more accurate x0
    sor_smoother(a_grids[0], x_grids[0], b_grids[0]);



};