#include "../include/arithmetic_tests.h"
#include "../include/common.h"

#include "../../include/arithmetic.h"
#include "../../include/grid.h"


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
