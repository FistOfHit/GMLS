#include "../include/arithmetic.h"
#include <cmath>
#include <cstddef>
#include <vector>


using vector = std::vector<float>;


void add(const vector &a, const vector &b, const int grid_depth,
    vector &result) {

    // Determine stride length across vector/matrix
    const auto stride = std::pow(2, grid_depth);

    for (auto i = 0; i < a.size(); i += stride) { result[i] = a[i] + b[i]; }
}


void subtract(const vector &a, const vector &b, const int grid_depth,
    vector &result) {

    // Determine stride length across vector/matrix
    const auto stride = std::pow(2, grid_depth);

    for (auto i = 0; i < a.size(); i += stride) { result[i] = a[i] - b[i]; }
}


void multiply(const vector &a, const vector &b, const int grid_depth,
    vector &result) {

    // Infer the dimensions of A from b and x
    const auto num_rows = result.size();
    const auto num_cols = b.size();

    // Determine stride length across vector/matrix
    const auto stride = std::pow(2, grid_depth);

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