#pragma once
#include <vector>


using vector = std::vector<float>;


void print_matrix(const vector &vector, const size_t num_rows, const size_t num_cols, const int precision = 3);
void print_vector(const vector &vector, const int precision = 3);
