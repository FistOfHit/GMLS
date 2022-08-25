#ifndef ARITHMETIC_TESTS_H
#define ARITHMETIC_TESTS_H
#endif

#include <vector>


using vector = std::vector<float>;


/* Test vector addition. */
void test_add(const vector &a, const vector &b,
    const vector &expected_values);


/* Test vector subtraction. */
void test_subtract(const vector &a, const vector &b,
    const vector &expected_values);


/* Test matrix-vector multiplication. */
void test_multiply(const vector &test_matrix, const vector &test_vector,
    const vector &expected_values);


/* Run all tests for arithmetic operators. */
void run_arithmetic_tests();