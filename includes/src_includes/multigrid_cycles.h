#include <vector>


using grid_list = std::map<int, std::vector<float>>;


// void w_cycle(std::vector<std::vector<float>> grids);
void v_cycle(grid_list a_grids, grid_sizes a_sizes, grid_list x_grids, grid_list b_grids, grid_list r_grids, const int num_iterations);