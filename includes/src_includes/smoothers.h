#pragma once
#include <vector>

using vector = std::vector<float>;
void jacobi_smooth(const vector &a, vector &x, const vector &b, const int grid_depth, const int num_iterations, const float omega = 2.0F/3);
void sor_smooth(const vector &a, vector &x, const vector &b, const int grid_depth, const int num_iterations, const float omega = 1.5F);
