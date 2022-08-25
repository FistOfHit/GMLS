#ifndef PRINTING_H
#define PRINTING_H
#endif

#include <vector>


using vector = std::vector<float>;


/* Print matrix element by element in easy to read manner.

Notes
-----
Printing is done as expected, but to make the it a bit nicer, first the
number of digits in each element is found and then we print it to 2 decimal
places, so that each element is printed with the same amount of space
around it. This keeps the printing clean and tidy, and avoids rows being
offset when printing, making it much easier to see down columns.

Parameters
----------
const std::vector<float> &matrix:
    The matrix to print
const size_t num_rows:
    The number of rows in the matrix
const size_t num_cols:
    The number of columns in the matrix
const size_t num_cols:
    The number of columns in the matrix
const int precision (default = 3):
    The numerical precision at which to print */
void print_matrix(const vector &vector, const size_t num_rows,
    const size_t num_cols, const int precision = 3);


/* Print vector element by element in easy to read manner.

Parameters
----------
const std::vector<float> &vector:
    The vector to print
const int precision (default = 3):
    The numerical precision at which to print */
void print_vector(const vector &vector, const int precision = 3);
