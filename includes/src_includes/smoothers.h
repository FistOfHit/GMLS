#pragma once
#include <vector>

using vector = std::vector<float>;
void jacobi_smooth(vector &a, vector &x, vector &b,  int grid_depth,  int num_iterations,  float omega = 2.0F/3);
void sor_smooth(vector &a, vector &x, vector &b, int grid_depth,  int num_iterations,  float omega = 1.5F);
