#include "../include/common.h"
#include "../include/smoothers_tests.h"

#include "../../include/grid.h"
#include "../../include/smoothers.h"


template <typename T>
void test_smoothers(
    const Grid<T>& test_matrix,
    const Grid<T>& test_grid,
    const Grid<T>& expected_values,
    const int num_iterations
) {
    Grid<T> actual = Grid<T>(expected_values.size(), expected_values.max_depth());
    sor_smooth(test_matrix, actual, test_grid, num_iterations);
    test_grid_equality(expected_values, actual);

    actual = Grid<T>(expected_values.size(), expected_values.max_depth());
    jacobi_smooth(test_matrix, actual, test_grid, num_iterations);
    test_grid_equality(expected_values, actual, 1e-3);
}
