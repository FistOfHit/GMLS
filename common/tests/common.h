#pragma once

#include "include/grid.h"


/// @brief Test if two grids are equal to within a given tolerance.
///
/// @param a
/// @param b
/// @param tolerance The permitted element-wise distance between a and b
void test_grid_equality(
    const Grid<float>& a,
    const Grid<float>& b,
    const float tolerance = 1e-5F
);


/// @brief Log a mismatch failure to stdout.
///
/// @param expected Expected results
/// @param actual   Actual results
void log_failure(const Grid<float>& expected, const Grid<float>& actual);
