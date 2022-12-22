#pragma once

#include "include/grid.h"


/// @brief Test Grid interpolation.
///
/// @param coarse          The coarse grid to interpolate
/// @param expected_values The expected value of the grid after interpolation
void test_grid_interpolation(const Grid<float>& coarse, const Grid<float>& expected_values);


/// @brief Test Grid restriction.
///
/// @param fine         The coarse grid to interpolate
/// @param expected_values The expected value of the grid after interpolation
void test_grid_restriction(const Grid<float>& fine, const Grid<float>& expected_values);
