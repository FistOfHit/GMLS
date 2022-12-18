#include "../include/common.h"
#include "../include/multigrid_cycle_tests.h"

#include "../../include/grid.h"
#include "../../include/multigrid_cycles.h"


template <typename T>
void test_v_cycle(
    Grid<T>& a,
    Grid<T>& b,
    Grid<T>& residual,
    Grid<T>& error,
    const Grid<T> expected_values,
    const int num_iterations,
    const int num_cycles
) {
    Grid<T> actual = Grid<T>(expected_values.size(), expected_values.max_depth());
    for (auto i = 0; i < num_cycles; i++) {
        v_cycle(a, actual, b, residual, error, num_iterations, 0);
    }
    test_grid_equality(expected_values, actual);
}


template <typename T>
void test_w_cycle(
    Grid<T>& a,
    Grid<T>& b,
    Grid<T>& residual,
    Grid<T>& error,
    const Grid<T> expected_values,
    const int num_iterations,
    const int num_cycles
) {
    Grid<T> actual = Grid<T>(expected_values.size(), expected_values.max_depth());
    for (auto i = 0; i < num_cycles; i++) {
        w_cycle(a, actual, b, residual, error, num_iterations);
    }
    test_grid_equality(expected_values, actual);
}
