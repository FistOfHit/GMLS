#include "../include/arithmetic.h"

#include "../include/grid.h"

#include <cmath>
#include <cstddef>


void add(Grid &a, Grid &b, Grid &result) {

    // Determine stride length across grid
    const auto stride = std::pow(2, a.depth);

    for (auto i = 0; i < a.size(); i += stride) { result[i] = a[i] + b[i]; }
}


void subtract(Grid &a, Grid &b, Grid &result) {

    // Determine stride length across grid
    const auto stride = std::pow(2, a.depth);

    for (auto i = 0; i < a.size(); i += stride) { result[i] = a[i] - b[i]; }
}


void multiply(Grid &a, Grid &b, Grid &result) {

    // Infer the dimensions of a from b and x
    const auto num_rows = result.size();
    const auto num_cols = b.size();

    // Determine stride length across grid
    const auto stride = std::pow(2, b.depth);

    float row_sum;
    size_t row_num;
    for (auto i = 0; i < num_rows; i += stride) {
        row_sum = 0.0f;
        row_num = i * num_cols;

        for (auto j = 0; j < num_cols; j += stride) {
            row_sum += a[row_num + j] * b[j];
        }

        result[i] = row_sum;
    }
}