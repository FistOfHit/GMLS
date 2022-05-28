#pragma once
#include <memory>
#include <string>
#include "matrix.h"


void print_matrix(std::unique_ptr<Matrix> matrix, int precision = 3);
void print_vector(std::vector<float> vector, int precision = 3);
