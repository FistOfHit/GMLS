#include "../include/arithmetic.h"
#include "../include/grid.h"

#include <cmath>
#include <cstddef>


template <typename T>
void add(const Grid<T>& a, const Grid<T>& b, Grid<T>& result) {
    for (auto i = 0; i < a.size(); i += a.stride()) { result[i] = a[i] + b[i]; }
}


template <typename T>
void subtract(const Grid<T>& a, const Grid<T>& b, Grid<T>& result) {
    for (auto i = 0; i < a.size(); i += a.stride()) { result[i] = a[i] - b[i]; }
}


template <typename T>
void multiply(const Grid<T>& a, const Grid<T>& b, Grid<T>& result) {

    float row_sum;
    size_t row_index;
    // Matrix-Vector multiplication (row-by-row element wise vector-vector)
    for (auto i = 0; i < a.num_rows(); i += a.stride()) {
        row_sum = 0.0F;
        row_index = i * b.size();

        for (auto j = 0; j < a.num_cols(); j += a.stride()) {
            row_sum += a[row_index + j] * b[j];
        }

        result[i] = row_sum;
    }
}
