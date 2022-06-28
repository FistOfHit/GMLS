#pragma once
#include <vector>

using vector = std::vector<float>;
void gs_smoother(const vector &lhs_matrix, vector &solution_vector, const vector &rhs_vector, const int num_iterations = -1);
void sor_smoother(const vector &lhs_matrix, vector &solution_vector, const vector &rhs_vector, const int num_iterations = -1, const int omega = 1.5);
