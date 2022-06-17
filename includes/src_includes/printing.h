#pragma once
#include <memory>
#include <string>
#include "matrix.h"


void print_matrix(Matrix<float> &matrix, const int precision = 3);
void print_vector(const std::vector<float> &vector, const int precision = 3);
