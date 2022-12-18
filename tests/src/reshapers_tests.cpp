#include "../include/common.h"
#include "../include/reshapers_tests.h"

#include "../../include/grid.h"


void test_grid_interpolation(
    const Grid<float>& coarse,
    const Grid<float>& expected_values
) {
    Grid<float> actual = coarse;

    actual.interpolate();
    coarse.depth--;

    test_grid_equality(expected_values, actual);
}


void test_grid_restriction(
    const Grid<float>& fine,
    const Grid<float>& expected_values
) {
    Grid<float> actual = fine;

    actual.restrict();
    fine.depth++;

    test_grid_equality(expected_values, actual);
}
