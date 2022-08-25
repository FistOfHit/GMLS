#ifndef ARITHMETIC_H
#define ARITHMETIC_H
#endif

#include <vector>


using vector = std::vector<float>;


/* Add two vectors together, element-wise into an output argument vector. */
void add(const vector &a, const vector &b, const int grid_depth,
    vector &result);


/* Subtract two vectors, element-wise into an output argument vector. */
void subtract(const vector &a, const vector &b, const int grid_depth,
    vector &result);


/* Perform a matrix vector product into an output argument vector. */
void multiply(const vector &a, const vector &b, const int grid_depth,
    vector &result);