#pragma once
#include <vector>

using vector = std::vector<float>;


void test_add(const vector &a, const vector &b,
    const vector &expected_values);
void test_subtract(const vector &a, const vector &b,
    const vector &expected_values);
void test_multiply(const vector &test_matrix, const size_t num_rows,
    const size_t num_cols, const vector &test_vector,
    const vector &expected_values);
void run_arithmetic_tests();