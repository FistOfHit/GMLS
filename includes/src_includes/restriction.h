#pragma once
#include <vector>


void restrict_vector(const std::vector<float> &fine_array, std::vector<float> &coarse_array);
void restrict_matrix(const std::vector<float> &fine_array, const int fine_rows, const int fine_cols, std::vector<float> &coarse_array, const int coarse_rows, const int coarse_cols);
