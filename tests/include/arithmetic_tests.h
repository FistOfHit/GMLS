#pragma once

#include "../../include/grid.h"


/// @brief Test Grid-Grid element-wise addition
///
/// @param a
/// @param b
/// @param expected_values
void test_add(
    const Grid<float> &a,
    const Grid<float> &b,
    const Grid<float> &expected_values
);


/// @brief Test Grid-Grid element-wise subtraction
///
/// @param a
/// @param b
/// @param expected_values
void test_subtract(
    const Grid<float>& a,
    const Grid<float>& b,
    const Grid<float>& expected_values
);


/// @brief Test Grid-Grid element-wise addition
///
/// @param matrix
/// @param b               The second grid argument
/// @param expected_values The expected output from the test
void test_multiply(
    const Grid<float>& matrix,
    const Grid<float>& vector,
    const Grid<float>& expected_values
);
