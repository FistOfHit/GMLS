#pragma once
#include <vector>

using vector = std::vector<float>;
void jacobi_smooth(const vector &lhs_matrix, vector &solution_vector, const vector &rhs_vector, const int num_iterations = -1);
void sor_smooth(const vector &a, vector &x, const vector &b, const int grid_depth, const int omega = 1.5, const int num_iterations = -1);
