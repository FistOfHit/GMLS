#pragma once
#include <vector>
#include "matrix.h"


void gs_smoother(Matrix<float> &lhs_matrix, std::vector<float> &solution_vector, const std::vector<float> &rhs_vector, const int num_iterations);
void sor_smoother(Matrix<float> &lhs_matrix, std::vector<float> &solution_vector, const std::vector<float> &rhs_vector, const int num_iterations, const int omega);
