#include "../include/common.h"
#include "../include/reshapers_tests.h"

#include "../../include/grid.h"
#include "../../include/reshapers.h"


template <typename T>
void test_grid_interpolation(
    const Grid<T>& coarse,
    const Grid<T>& expected_values
) {
    Grid<T> actual = coarse;

    interpolate_vector(actual);
    coarse.depth--;

    test_grid_equality(expected_values, actual);
}


template <typename T>
void test_grid_restriction(
    const Grid<T>& fine,
    const Grid<T>& expected_values
) {
    Grid<T> actual = fine;

    restrict_vector(actual);
    fine.depth++;

    test_grid_equality(expected_values, actual);
}
