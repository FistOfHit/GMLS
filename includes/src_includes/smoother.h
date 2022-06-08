#pragma once
#include <vector>
#include "matrix.h"


void gs_smoother(Matrix &lhs_matrix, std::vector<double> &solution_vector, std::vector<double> &rhs_vector, int num_iterations);
void sor_smoother(Matrix &lhs_matrix, std::vector<double> &solution_vector, std::vector<double> &rhs_vector, int num_iterations, int omega);
