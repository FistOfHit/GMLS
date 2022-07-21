#include "../includes/src_includes/arithmetic.h"
#include <math.h>
#include <vector>


using vector = std::vector<float>;


void add(const vector &a, const vector &b, const int grid_depth,
    vector &result) {
    /* Add two vectors together, element-wise into an output argument vector. */

    // Determine stride length across vector/matrix
    const auto stride = std::pow(2, grid_depth);

    for (auto i = 0; i < a.size(); i += stride) { result[i] = a[i] + b[i]; }
}


void subtract(const vector &a, const vector &b, const int grid_depth,
    vector &result) {
    /* Subtract two vectors, element-wise into an output argument vector. */

    // Determine stride length across vector/matrix
    const auto stride = std::pow(2, grid_depth);

    for (auto i = 0; i < a.size(); i += stride) { result[i] = a[i] - b[i]; }
}


void multiply(const vector &a, const vector &b, const int grid_depth,
    vector &result) {
    /* Perform a matrix vector product into an output argument vector. */

    // Infer the dimensions of A from b
    const auto num_rows = b.size();

    // Determine stride length across vector/matrix
    const auto stride = std::pow(2, grid_depth);

    float row_sum;
    size_t row_num;
    for (auto i = 0; i < num_rows; i += stride) {
        row_sum = 0.0F;
        row_num = i * num_rows;

        for (auto j = 0; j < num_rows; j += stride) {
            row_sum += a[row_num + j] * b[j];
        }

        result[i] = row_sum;
    }
}