#ifndef ARITHMETIC_H
#define ARITHMETIC_H
#endif

#include "../include/grid.h"


/* Add two vectors together, element-wise into an output argument vector. */
void add(Grid &a, Grid &b, Grid &result);


/* Subtract two vectors, element-wise into an output argument vector. */
void subtract(Grid &a, Grid &b, Grid &result);


/* Perform a matrix vector product into an output argument vector. */
void multiply(Grid &a, Grid &b, Grid &result);
