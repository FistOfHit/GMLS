#pragma once

#include "../../include/grid.h"


/* Test Grid interpolation. */
void test_grid_interpolation(const Grid &coarse, const Grid &expected_values);


/* Test Grid restriction. */
void test_grid_restriction(const Grid &fine, const Grid &expected_values);

/* Run all tests for reshape operators. */
void run_reshapers_tests();
