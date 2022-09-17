#pragma once

#include "grid.h"


/* Add two vectors together, element-wise into an output argument vector. */
void add(const Grid &a, const Grid &b, Grid &result);


/* Subtract two vectors, element-wise into an output argument vector. */
void subtract(const Grid &a, const Grid &b, Grid &result);


/* Perform a matrix vector product into an output argument vector. */
void multiply(const Grid &a, const Grid &b, Grid &result);
