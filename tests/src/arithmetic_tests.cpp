#include "../include/arithmetic_tests.h"
#include "../include/common.h"

#include "../../include/arithmetic.h"
#include "../../include/grid.h"
#include "../../include/printing.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <map>
#include <vector>


template <typename T>
void test_add(
    const Grid<T>& a,
    const Grid<T>& b,
    const Grid<T>& expected_values
) {
    Grid<T> actual = Grid<T>(a.size(), 0);
    add(a, b, actual);
    test_grid_equality(expected_values, actual);
}


template <typename T>
void test_subtract(
    const Grid<T>& a,
    const Grid<T>& b,
    const Grid<T>& expected_values
) {
    Grid<T> actual = Grid<T>(a.size(), 0);
    subtract(a, b, actual);
    test_grid_equality(expected_values, actual);
}


template <typename T>
void test_multiply(
    const Grid<T>& test_matrix,
    const Grid<T>& test_grid,
    const Grid<T>& expected_values
) {
    Grid<T> actual = Grid<T>(test_grid.size(), 0);
    multiply(test_matrix, test_grid, actual);
    test_grid_equality(expected_values, actual);
}


void run_arithmetic_tests() {

    std::cout << "Vector-Vector addition/subtraction tests: \n";
    // 0 +- 0 = 0
    Grid<float> a = Grid<float>(5, 1);
    Grid<float> b = Grid<float>(5, 1);
    Grid<float> expected_values = Grid<float>(5, 1);
    test_add(a, b, expected_values);
    test_subtract(a, b, expected_values);

    // x +- 0 = x
    a = Grid<float>(std::vector<float>{1, 2, 3, 4, 5}, 1);
    b = Grid<float>(5, 1);
    expected_values = Grid<float>(std::vector<float>{1, 2, 3, 4, 5}, 1);;
    test_add(a, b, expected_values);
    test_subtract(a, b, expected_values);

    // 0 +- x = +-x
    a = Grid<float>(5, 1);
    b = Grid<float>(std::vector<float>{1, 2, 3, 4, 5}, 1);
    expected_values = Grid<float>(std::vector<float>{1, 2, 3, 4, 5}, 1);
    test_add(a, b, expected_values);
    expected_values = Grid<float>(std::vector<float>{-1, -2, -3, -4, -5}, 1);
    test_subtract(a, b, expected_values);

    // x - x = 0
    a = Grid<float>(std::vector<float>{1, 2, 3, 4, 5}, 1);
    b = Grid<float>(std::vector<float>{1, 2, 3, 4, 5}, 1);
    expected_values = Grid<float>(5, 0);
    test_subtract(a, b, expected_values);

    // x +- y = x +- y
    a = Grid<float>(std::vector<float>{1, 2, 3, 4, 5}, 1);
    b = Grid<float>(std::vector<float>{3, 3, 3, 3, 3}, 1);
    expected_values = Grid<float>(std::vector<float>{4, 5, 6, 7, 8}, 1);
    test_add(a, b, expected_values);
    expected_values = Grid<float>(std::vector<float>{-2, -1, 0, 1, 2}, 1);
    test_subtract(a, b, expected_values);

    std::cout << "Matrix-Vector multiplication tests: \n";
    const auto num_rows = 3;
    const auto num_cols = 3;
    // Diagonal matricies
    // 0 * 0 = 0
    a = Grid<float>(num_rows, num_cols, 1);
    b = Grid<float>(num_rows, 1);
    expected_values = Grid<float>(num_rows, 1);
    test_multiply(a, b, expected_values);

    // 0 * x = 0
    a = Grid<float>(num_rows, num_cols, 1);
    b = Grid<float>(num_rows, 1);
    expected_values = Grid<float>(num_rows, 1);
    test_multiply(a, b, expected_values);

    // x * 0 = 0
    a = Grid<float>(std::vector<float>{
        1, 0, 0,
        0, 1, 0,
        0, 0, 1,
    }, num_rows, num_cols, 1);
    b = Grid<float>(num_rows, 1);
    expected_values = Grid<float>(num_rows, 1);
    test_multiply(a, b, expected_values);

    // Next two tests also test reversibility of this transform
    // 1 * x = x
    a = Grid<float>(std::vector<float>{
        1, 0, 0,
        0, 1, 0,
        0, 0, 1,
    }, num_rows, num_cols, 1);
    b = Grid<float>(std::vector<float>{3, 3, 3}, 1);
    expected_values = Grid<float>(std::vector<float>{3, 3, 3}, 1);
    test_multiply(a, b, expected_values);

    // x * 1 = x
    a = Grid<float>(std::vector<float>{
        3, 0, 0,
        0, 3, 0,
        0, 0, 3,
    }, num_rows, num_cols, 1);
    b = Grid<float>(std::vector<float>{1, 1, 1}, 1);
    expected_values = Grid<float>(std::vector<float>{3, 3, 3}, 1);
    test_multiply(a, b, expected_values);

    // x * 1/x = 1
    a = Grid<float>(std::vector<float>{
        3, 0, 0,
        0, 3, 0,
        0, 0, 3,
    }, num_rows, num_cols, 1);
    b = Grid<float>({1.0F/3, 1.0F/3, 1.0F/3}, 1);
    expected_values = Grid<float>(std::vector<float>{1, 1, 1}, 1);
    test_multiply(a, b, expected_values);
    
    // Non-diagonal matricies
    // x * y = x * y
    a = Grid<float>(std::vector<float>{
        1, 2, 3,
        4, 5, 6,
        7, 8, 9,
    }, num_rows, num_cols, 1);
    b = Grid<float>(std::vector<float>{1, 2, 3}, 1);
    expected_values = Grid<float>(std::vector<float>{14, 32, 50}, 1);
    test_multiply(a, b, expected_values);
}