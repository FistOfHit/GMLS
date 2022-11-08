#pragma once

#include "grid.h"


/// @brief Print out a grid element by element in easy to read manner.
///
/// @details Printing is done as expected, but to make the it a bit nicer,
/// first the number of digits in each element is found and then we print it
/// to 2 decimal places, so that each element is printed with the same amount
/// of space around it. This keeps the printing clean and tidy, and avoids rows
/// being offset when printing, making it much easier to see down columns.
///
/// @param grid      The grid to print
/// @param precision The numerical precision at which to print (default = 3)
template <typename T>
void print_grid(const Grid<T>& grid, const int precision = 3);
