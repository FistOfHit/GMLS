#include "tests/include/common.h"
#include "tests/include/smoothers_tests.h"

#include "include/grid.h"
#include "include/smoothers.h"


void test_smoothers(
    const Grid<float>& test_matrix,
    const Grid<float>& test_grid,
    const Grid<float>& expected_values,
    const int num_iterations
) {
    Grid<float> actual = Grid<float>(expected_values.size(), expected_values.max_depth());
    sor_smooth(test_matrix, actual, test_grid, num_iterations);
    test_grid_equality(expected_values, actual);

    actual = Grid<float>(expected_values.size(), expected_values.max_depth());
    jacobi_smooth(test_matrix, actual, test_grid, num_iterations);
    test_grid_equality(expected_values, actual, 1e-3);
}
