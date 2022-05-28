#pragma once

#include <vector>
#include "matrix.h"


void restrict_vector(std::vector<int> fine_array, std::vector<int> coarse_array);

void restrict_matrix(Matrix fine_matrix, Matrix coarse_matrix);
