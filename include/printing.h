#pragma once

#include "grid.h"


/* Print out a grid element by element in easy to read manner.

Notes
-----
Printing is done as expected, but to make the it a bit nicer, first the
number of digits in each element is found and then we print it to 2 decimal
places, so that each element is printed with the same amount of space
around it. This keeps the printing clean and tidy, and avoids rows being
offset when printing, making it much easier to see down columns.

Parameters
----------
Grid &grid:
    The grid to print
const int precision (default = 3):
    The numerical precision at which to print */
void print_grid(const Grid &grid, const int precision = 3);
