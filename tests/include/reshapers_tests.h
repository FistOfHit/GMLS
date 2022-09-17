#pragma once

#include "../../include/grid.h"


/* Test Grid interpolation. */
void test_Grid_interpolation(const Grid &coarse, const Grid &expected_values,
    const int grid_depth = 1);


/* Test Grid restriction. */
void test_Grid_restriction(const Grid &fine, const Grid &expected_values,
    const int grid_depth = 0);

/* Run all tests for reshape operators. */
void run_reshapers_tests();
