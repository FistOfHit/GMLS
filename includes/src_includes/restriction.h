#pragma once
#include <memory>
#include <vector>
#include "matrix.h"


void restrict_vector(const std::vector<float> &fine_array, std::vector<float> &coarse_array);
void restrict_matrix(Matrix<float> &fine_matrix, Matrix<float> &coarse_matrix);
