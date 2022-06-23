#pragma once
#include <vector>


void gs_smoother(const std::vector<float> &lhs_matrix, std::vector<float> &solution_vector, const std::vector<float> &rhs_vector, const int num_iterations = -1);
void sor_smoother(const std::vector<float> &lhs_matrix, std::vector<float> &solution_vector, const std::vector<float> &rhs_vector, const int num_iterations = -1, const int omega = 1.5);
