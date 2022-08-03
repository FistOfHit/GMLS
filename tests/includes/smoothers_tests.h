#pragma once
#include <vector>


using vector = std::vector<float>;


void test_smoothers(const vector &test_matrix, const vector &test_vector,
    const vector &expected_values, const int grid_depth = 0,
    const int num_iterations = 100);
void run_smoother_tests();
