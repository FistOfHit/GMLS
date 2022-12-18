#pragma once

#include "../../include/grid.h"


/// @brief Test smoothers.
///
/// @param test_matrix
/// @param test_grid
/// @param expected_values 
/// @param num_iterations The number of smoother iterations (default: 100)
void test_smoothers(
    const Grid<float>& test_matrix,
    const Grid<float>& test_grid,
    const Grid<float>& expected_values,
    const int num_iterations = 100
);
