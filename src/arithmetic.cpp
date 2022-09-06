#include "../include/arithmetic.h"

#include "../include/grid.h"

#include <cmath>
#include <cstddef>


void add(Grid &a, Grid &b, Grid &result) {
    for (auto i = 0; i < a.size(); i += a.stride()) { result[i] = a[i] + b[i]; }
}


void subtract(Grid &a, Grid &b, Grid &result) {
    for (auto i = 0; i < a.size(); i += a.stride()) { result[i] = a[i] - b[i]; }
}


void multiply(Grid &a, Grid &b, Grid &result) {

    float row_sum;
    size_t row_num;
    // Infer size of A from size of result and b
    for (auto i = 0; i < result.size(); i += a.stride()) {
        row_sum = 0.0f;
        row_num = i * b.size();

        for (auto j = 0; j < b.size(); j += a.stride()) {
            row_sum += a[row_num + j] * b[j];
        }

        result[i] = row_sum;
    }
}
