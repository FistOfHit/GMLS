#pragma once

#include "../../include/grid.h"


/// @brief Test Grid interpolation.
///
/// @param coarse          The coarse grid to interpolate
/// @param expected_values The expected value of the grid after interpolation
template <typename T>
void test_grid_interpolation(const Grid<T>& coarse, const Grid<T>& expected_values);


/// @brief Test Grid restriction.
///
/// @param fine         The coarse grid to interpolate
/// @param expected_values The expected value of the grid after interpolation
template <typename T>
void test_grid_restriction(const Grid<T>& fine, const Grid<T>& expected_values);


/// @brief Run all tests for reshape operators.
void run_reshapers_tests();
