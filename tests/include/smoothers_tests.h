#pragma once

#include "../../include/grid.h"


/* Test smoothers. */
void test_smoothers(const Grid &test_matrix, const Grid &test_Grid,
    const Grid &expected_values, const int grid_depth = 0,
    const int num_iterations = 100);


/* Run all smoother tests. */
void run_smoother_tests();
