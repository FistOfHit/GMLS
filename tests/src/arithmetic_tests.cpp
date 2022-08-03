#include <algorithm>
#include <iostream>
#include <map>
#include <math.h>
#include <vector>
#include "../../includes/arithmetic.h"
#include "../../includes/printing.h"
#include "../includes/arithmetic_tests.h"
#include "../includes/common.h"


using vector = std::vector<float>;


void test_add(const vector &a, const vector &b,
    const vector &expected_values) {
    /* Test vector addition. */
    vector actual = vector(a.size(), 0);
    add(a, b, 0, actual);
    test_vector_equality(expected_values, actual);

    actual = vector();
}


void test_subtract(const vector &a, const vector &b,
    const vector &expected_values) {
    /* Test vector subtraction. */
    vector actual = vector(a.size(), 0);
    subtract(a, b, 0, actual);
    test_vector_equality(expected_values, actual);

    actual = vector();
}


void test_multiply(const vector &test_matrix, const size_t num_rows,
    const vector &test_vector, const vector &expected_values) {
    /* Test matrix-vector multiplication. */
    vector actual = vector(num_rows, 0);
    multiply(test_matrix, test_vector, 0, actual);
    test_vector_equality(expected_values, actual);

    actual = vector();
}


void run_arithmetic_tests() {
    /* Run all tests for arithmetic operators. */
    vector a;
    vector b;
    vector expected_values;

    std::cout << "Vector-Vector addition/subtraction tests: \n";
    // 0 +- 0 = 0
    a = vector(5, 0);
    expected_values = vector(5, 0);
    test_add(a, a, expected_values);
    test_subtract(a, a, expected_values);

    // x +- 0 = x
    a = vector{1, 2, 3, 4, 5};
    b = vector(5, 0);
    expected_values = a;
    test_add(a, b, expected_values);
    test_subtract(a, b, expected_values);

    // 0 +- x = +-x
    test_add(b, a, expected_values);
    expected_values = vector{-1, -2, -3, -4, -5};
    test_subtract(b, a, expected_values);

    // x - x = 0
    expected_values = vector(5, 0);
    test_subtract(a, a, expected_values);

    // x +- y = x +- y
    a = vector{1, 2, 3, 4, 5};
    b = vector{3, 3, 3, 3, 3};
    expected_values = vector{4, 5, 6, 7, 8};
    test_add(b, a, expected_values);
    expected_values = vector{2, 1, 0, -1, -2};
    test_subtract(b, a, expected_values);

    std::cout << "Matrix-Vector multiplication tests: \n";
    const auto num_rows = 3;
    const auto num_cols = 3;
    // Diagonal matricies
    // 0 * 0 = 0
    a = vector(num_rows * num_cols, 0);
    b = vector(num_rows, 0);
    expected_values = vector(num_rows, 0);
    test_multiply(a, num_rows, b, b);

    // 0 * x = 0
    b = vector(num_rows, 1);
    test_multiply(a, num_rows, b, expected_values);

    // x * 0 = 0
    a = vector{
        1, 0, 0,
        0, 1, 0,
        0, 0, 1,
    };
    b = vector(num_rows, 0);
    test_multiply(a, num_rows, b, expected_values);

    // Next two tests also test reversibility of this transform
    // 1 * x = x
    b = vector(num_rows, 3);
    test_multiply(a, num_rows, b, b);

    // x * 1 = x
    a = vector{
        3, 0, 0,
        0, 3, 0,
        0, 0, 3,
    };
    b = vector(num_rows, 1);
    expected_values = vector(num_rows, 3);
    test_multiply(a, num_rows, b, expected_values);

    // x * 1/x = 1
    b = vector(num_rows, 1.0F/3);
    expected_values = vector(num_rows, 1);
    test_multiply(a, num_rows, b, expected_values);
    
    // Non-diagonal matricies
    // x * y = x.y
    a = vector{
        1, 2, 3,
        4, 5, 6,
        7, 8, 9,
    };
    b = vector{1, 2, 3};
    expected_values = vector{14, 32, 50};
    test_multiply(a, num_rows, b, expected_values);

    a = vector();
    b = vector();
    expected_values = vector();
}