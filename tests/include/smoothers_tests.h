#pragma once

#include "../../include/grid.h"


/// @brief Test smoothers.
///
/// @param test_matrix
/// @param test_grid
/// @param expected_values 
/// @param num_iterations The number of smoother iterations (default: 100)
template <typename T>
void test_smoothers(
    const Grid<T>& test_matrix,
    const Grid<T>& test_grid,
    const Grid<T>& expected_values,
    const int num_iterations = 100
);
