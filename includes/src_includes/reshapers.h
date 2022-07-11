#pragma once
#include <vector>


using vector = std::vector<float>;


void interpolate_vector(vector &vector, const int grid_depth);
void restrict_vector(vector &vector, const int grid_depth);
