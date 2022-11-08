#pragma once

#include "../../include/grid.h"


/// @brief Test Grid-Grid element-wise addition
///
/// @param a
/// @param b
/// @param expected_values
template <typename T>
void test_add(
    const Grid<T> &a,
    const Grid<T> &b,
    const Grid<T> &expected_values
);


/// @brief Test Grid-Grid element-wise subtraction
///
/// @param a
/// @param b
/// @param expected_values
template <typename T>
void test_subtract(
    const Grid<T>& a,
    const Grid<T>& b,
    const Grid<T>& expected_values
);


/// @brief Test Grid-Grid element-wise addition
///
/// @param matrix
/// @param b               The second grid argument
/// @param expected_values The expected output from the test
template <typename T>
void test_multiply(
    const Grid<T>& matrix,
    const Grid<T>& vector,
    const Grid<T>& expected_values
);


/// @brief Run all arithmetic tests
void run_arithmetic_tests();
