#pragma once
#include <vector>


void restrict_vector(const std::vector<float> &fine_array, std::vector<float> &coarse_array);
void restrict_matrix(const std::vector<float> &fine_array, const size_t fine_rows, const size_t fine_cols, std::vector<float> &coarse_array, const size_t coarse_rows, const size_t coarse_cols);
