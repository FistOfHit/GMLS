#pragma once
#include <vector>


using vector = std::vector<float>;


void restrict_vector(vector &vector, const int grid_depth);
void interpolate_vector(vector &vector, const int grid_depth);

void restrict_matrix(vector &matrix, const int grid_depth);
void interpolate_matrix(vector &matrix, const int grid_depth);
