#pragma once

/* 
Headers
*/
#include "grid.h"


/*
\brief Add two vectors together, element-wise into an output argument vector.

\param &a      A grid
\param &b      Another grid
\param &result (Output parameter) the result of the operation
*/
void add(const Grid &a, const Grid &b, Grid &result);


/* 
\brief Subtract two vectors, element-wise into an output argument vector.

\param &a      A grid
\param &b      Another grid
\param &result (Output parameter) the result of the operation
*/
void subtract(const Grid &a, const Grid &b, Grid &result);


/*
\brief Perform a matrix vector product into an output argument vector.

\param &a      A grid
\param &b      Another grid
\param &result (Output parameter) the result of the operation
*/
void multiply(const Grid &a, const Grid &b, Grid &result);
