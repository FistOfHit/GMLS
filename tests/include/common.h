#pragma once

#include "../../include/grid.h"


/* Test if two grids are equal to within a given tolerance. */
void test_grid_equality(const Grid &a, const Grid &b, const float tolerance = 0.00001F);


/* Log a mismatch failure to stdout. */
void log_failure(const Grid &expected, const Grid &actual);
