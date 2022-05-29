#pragma once
#include <memory>
#include <vector>
#include "matrix.h"


void restrict_vector(std::vector<double> fine_array, std::vector<double> coarse_array);
void restrict_matrix(Matrix fine_matrix, Matrix coarse_matrix);
