#pragma once
#include <vector>


using vector = std::vector<float>;


void test_vector_interpolation(const vector &coarse,
    const vector &expected_values, const int grid_depth = 1);
void test_vector_restriction(const vector &fine, const vector &expected_values,
    const int grid_depth = 0);
void run_reshapers_tests();
