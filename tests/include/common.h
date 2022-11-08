#pragma once

#include "../../include/grid.h"


/// @brief Test if two grids are equal to within a given tolerance.
///
/// @param a
/// @param b
/// @param tolerance The permitted element-wise distance between a and b
template <typename T>
void test_grid_equality(
    const Grid<T>& a,
    const Grid<T>& b,
    const float tolerance = 1e-5F
);


/// @brief Log a mismatch failure to stdout.
///
/// @param expected Expected results
/// @param actual   Actual results
template <typename T>
void log_failure(const Grid<T>& expected, const Grid<T>& actual);
