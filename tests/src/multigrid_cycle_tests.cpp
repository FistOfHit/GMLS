#include "../include/common.h"
#include "../include/multigrid_cycle_tests.h"

#include "../../include/grid.h"
#include "../../include/multigrid_cycles.h"


void test_v_cycle(
    Grid<float>& a,
    Grid<float>& b,
    Grid<float>& residual,
    Grid<float>& error,
    const Grid<float> expected_values,
    const int num_iterations,
    const int num_cycles
) {
    Grid<float> actual = Grid<float>(expected_values.size(), expected_values.max_depth());
    for (auto i = 0; i < num_cycles; i++) {
        v_cycle(a, actual, b, residual, error, num_iterations, 0);
    }
    test_grid_equality(expected_values, actual);
}


void test_w_cycle(
    Grid<float>& a,
    Grid<float>& b,
    Grid<float>& residual,
    Grid<float>& error,
    const Grid<float> expected_values,
    const int num_iterations,
    const int num_cycles
) {
    Grid<float> actual = Grid<float>(expected_values.size(), expected_values.max_depth());
    for (auto i = 0; i < num_cycles; i++) {
        w_cycle(a, actual, b, residual, error, num_iterations);
    }
    test_grid_equality(expected_values, actual);
}
