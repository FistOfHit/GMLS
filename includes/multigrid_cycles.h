#pragma once
#include <vector>


using vector = std::vector<float>;


void v_cycle(vector &a, vector &x, vector &b, vector &r, vector&e, 
    const int num_grids, const int num_iterations);
void w_cycle(vector &a, vector &x, vector &b, vector &r, vector&e, 
    const int num_grids, const int num_iterations);