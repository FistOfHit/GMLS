#include "../include/arithmetic_tests.h"

#include "../../include/arithmetic.h"
#include "../../include/grid.h"
#include "../../include/printing.h"

#include "../include/common.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <map>
#include <vector>


using vector = std::vector<float>;


void test_add(const Grid &a, const Grid &b, const Grid &expected_values) {

    Grid actual = Grid(a.size(), 0);
    add(a, b, actual);
    test_grid_equality(expected_values, actual);
}


void test_subtract(const Grid &a, const Grid &b, const Grid &expected_values) {

    Grid actual = Grid(a.size(), 0);
    subtract(a, b, actual);
    test_grid_equality(expected_values, actual);
}


void test_multiply(const Grid &test_matrix, const size_t num_rows,
    const Grid &test_grid, const Grid &expected_values) {

    Grid actual = Grid(num_rows, 0);
    multiply(test_matrix, test_grid, actual);
    test_grid_equality(expected_values, actual);
}


void run_arithmetic_tests() {

    std::cout << "Grid-Grid addition/subtraction tests: \n";
    // 0 +- 0 = 0
    Grid a = Grid(5, 0);
    Grid expected_values = Grid(5, 0);
    test_add(a, a, expected_values);
    test_subtract(a, a, expected_values);

    // x +- 0 = x
    a = Grid(vector{1, 2, 3, 4, 5}, 1);
    Grid b = Grid(5, 0);
    expected_values = a;
    test_add(a, b, expected_values);
    test_subtract(a, b, expected_values);

    // 0 +- x = +-x
    test_add(b, a, expected_values);
    expected_values = Grid(vector{-1, -2, -3, -4, -5}, 1);
    test_subtract(b, a, expected_values);

    // x - x = 0
    expected_values = Grid(5, 0);
    test_subtract(a, a, expected_values);

    // x +- y = x +- y
    a = Grid(vector{1, 2, 3, 4, 5}, 1);
    b = Grid(vector{3, 3, 3, 3, 3}, 1);
    expected_values = Grid(vector{4, 5, 6, 7, 8}, 1);
    test_add(b, a, expected_values);
    expected_values = Grid(vector{2, 1, 0, -1, -2}, 1);
    test_subtract(b, a, expected_values);

    std::cout << "Matrix-Grid multiplication tests: \n";
    const auto num_rows = 3;
    const auto num_cols = 3;
    // Diagonal matricies
    // 0 * 0 = 0
    a = Grid(num_rows * num_cols, 0);
    b = Grid(num_rows, 0);
    expected_values = Grid(num_rows, 0);
    test_multiply(a, num_rows, b, b);

    // 0 * x = 0
    b = Grid(num_rows, 1);
    test_multiply(a, num_rows, b, expected_values);

    // x * 0 = 0
    a = Grid(vector{
        1, 0, 0,
        0, 1, 0,
        0, 0, 1,
    }, 1);
    b = Grid(num_rows, 0);
    test_multiply(a, num_rows, b, expected_values);

    // Next two tests also test reversibility of this transform
    // 1 * x = x
    b = Grid(num_rows, 3);
    test_multiply(a, num_rows, b, b);

    // x * 1 = x
    a = Grid(vector{
        3, 0, 0,
        0, 3, 0,
        0, 0, 3,
    }, 1);
    b = Grid(num_rows, 1);
    expected_values = Grid(num_rows, 3);
    test_multiply(a, num_rows, b, expected_values);

    // x * 1/x = 1
    b = Grid(num_rows, 1.0F/3);
    expected_values = Grid(num_rows, 1);
    test_multiply(a, num_rows, b, expected_values);
    
    // Non-diagonal matricies
    // x * y = x.y
    a = Grid(vector{
        1, 2, 3,
        4, 5, 6,
        7, 8, 9,
    }, 1);
    b = Grid{1, 2, 3};
    expected_values = Grid{14, 32, 50};
    test_multiply(a, num_rows, b, expected_values);
}