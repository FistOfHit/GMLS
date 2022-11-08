#include "../include/common.h"
#include "../include/multigrid_cycle_tests.h"

#include "../../include/grid.h"
#include "../../include/multigrid_cycles.h"
#include "../../include/printing.h"

#include <cmath>
#include <iostream>
#include <vector>


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


void run_cycle_tests() {

    std::cout << "V/W-cycle tests: \n";
    // Solving Ix = b
    auto num_cycles = 1;
    auto num_iterations = 3;
    auto num_rows = std::pow(2, 8) + 1;
    auto num_cols = std::pow(2, 8) + 1;
    auto max_depth = 3;

    // Creating Identity matrix
    Grid<float> a = Grid<float>(num_rows, num_cols, max_depth);
    for (auto i = 0; i < num_rows; i++) { a[i*num_rows + i] = 1; }

    // Arbitrary LHS vector b
    Grid<float> b = Grid<float>(std::vector<float>(num_rows, 7), max_depth);
    Grid<float> residual = Grid<float>(num_rows, max_depth);
    Grid<float> error = Grid<float>(num_cols, max_depth);
    Grid<float> expected_values = Grid<float>(std::vector<float>(num_rows, 7), max_depth);

    test_v_cycle(a, b, residual, error, expected_values, num_iterations, num_cycles);
    test_w_cycle(a, b, residual, error, expected_values, num_iterations, num_cycles);

    // Solving small Ax = b
    num_cycles = 200;
    num_iterations = 10;
    num_rows = 9;
    num_cols = 9;
    max_depth = 2;

    // SPD matrix formed from generating random A and getting A*(A^T)
    a = Grid<float>(std::vector<float>{
        385, 317, 310, 338, 237, 295, 265, 358, 200,
        317, 325, 261, 295, 226, 306, 238, 305, 204,
        310, 261, 284, 266, 184, 262, 207, 303, 170,
        338, 295, 266, 350, 201, 254, 226, 305, 190,
        237, 226, 184, 201, 249, 236, 249, 177, 152,
        295, 306, 262, 254, 236, 327, 240, 266, 197,
        265, 238, 207, 226, 249, 240, 285, 211, 176,
        358, 305, 303, 305, 177, 266, 211, 413, 192,
        200, 204, 170, 190, 152, 197, 176, 192, 157,
    }, num_rows, num_cols, max_depth);
    b = Grid<float>(std::vector<float>{
        0, 2, 4, 5, 8, 8, 2, 6, 3,
    }, max_depth);

    residual = Grid<float>(num_rows, max_depth);
    error = Grid<float>(num_cols, max_depth);

    /// Verified with python numpy.linalg.solve()
    expected_values = Grid<float>(std::vector<float>{
        -0.67194828,
        -0.97521385,
        -0.28943875,
        0.60827349,
        0.33842962,
        0.74207787,
        -0.07373032,
        0.56177135,
        -0.14361974,
    }, max_depth);

    test_v_cycle(a, b, residual, error, expected_values, num_iterations, num_cycles);
    test_w_cycle(a, b, residual, error, expected_values, num_iterations, num_cycles);

    /// @todo Solving larger Ax = b
}