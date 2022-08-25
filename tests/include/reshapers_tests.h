#ifndef RESHAPERS_TESTS_H
#define RESHAPERS_TESTS_H
#endif

#include <vector>


using vector = std::vector<float>;


/* Test vector interpolation. */
void test_vector_interpolation(const vector &coarse,
    const vector &expected_values, const int grid_depth = 1);


/* Test vector restriction. */
void test_vector_restriction(const vector &fine, const vector &expected_values,
    const int grid_depth = 0);

/* Run all tests for reshape operators. */
void run_reshapers_tests();
