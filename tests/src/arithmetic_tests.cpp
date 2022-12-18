#include "../include/arithmetic_tests.h"
#include "../include/common.h"

#include "../../include/grid.h"


void test_add(
    const Grid<float>& a,
    const Grid<float>& b,
    const Grid<float>& expected_values
) {
    Grid<float> actual = Grid<float>(a.size(), 0);
    // add(a, b, actual);
    actual = a + b;
    test_grid_equality(expected_values, actual);
}


void test_subtract(
    const Grid<float>& a,
    const Grid<float>& b,
    const Grid<float>& expected_values
) {
    Grid<float> actual = Grid<float>(a.size(), 0);
    // subtract(a, b, actual);
    actual = a - b;
    test_grid_equality(expected_values, actual);
}


void test_multiply(
    const Grid<float>& test_matrix,
    const Grid<float>& test_grid,
    const Grid<float>& expected_values
) {
    Grid<float> actual = Grid<float>(test_grid.size(), 0);
    // multiply(test_matrix, test_grid, actual);
    actual = test_matrix * test_grid;
    test_grid_equality(expected_values, actual);
}
