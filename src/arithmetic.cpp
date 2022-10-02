#include "../include/arithmetic.h"

#include "../include/grid.h"

#include <cmath>
#include <cstddef>

void add(const Grid &a, const Grid &b, Grid &result) {
    for (auto i = 0; i < a.size(); i += a.stride()) { result[i] = a[i] + b[i]; }
}


void subtract(const Grid &a, const Grid &b, Grid &result) {
    for (auto i = 0; i < a.size(); i += a.stride()) { result[i] = a[i] - b[i]; }
}


void multiply(const Grid &a, const Grid &b, Grid &result) {

    float row_sum;
    size_t row_num;
    for (auto i = 0; i < a.num_rows(); i += a.stride()) {
        row_sum = 0.0F;
        row_num = i * b.size();

        for (auto j = 0; j < a.num_cols(); j += a.stride()) {
            row_sum += a[row_num + j] * b[j];
        }

        result[i] = row_sum;
    }
}
