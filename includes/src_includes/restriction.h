#pragma once
#include <memory>
#include <vector>
#include "matrix.h"


void restrict_vector(std::vector<int> fine_array, std::vector<int> coarse_array);
void restrict_matrix(std::unique_ptr<Matrix> fine_matrix, std::unique_ptr<Matrix> coarse_matrix);
