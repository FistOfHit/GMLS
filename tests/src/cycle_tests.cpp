#include "../include/common.h"
#include "../include/cycle_tests.h"
#include "../../include/multigrid_cycles.h"
#include "../../include/printing.h"
#include <cmath>
#include <iostream>
#include <vector>


using vector = std::vector<float>;


void test_v_cycle(Grid &a, Grid &b, Grid &residual, Grid &error,
    const Grid expected_values, const int num_grids, const int num_iterations,
    const int num_cycles) {

    Grid actual = Grid(expected_values.size(), 3);
    for (auto i = 0; i < num_cycles; i++) {
        v_cycle(a, actual, b, residual, error, num_grids, num_iterations);
    }
    test_grid_equality(expected_values, actual);
}


void test_w_cycle(Grid &a, Grid &b, Grid &residual, Grid& error,
    const Grid expected_values, const int num_grids,
    const int num_iterations, const int num_cycles) {

    Grid actual = Grid(expected_values.size(), 3);
    for (auto i = 0; i < num_cycles; i++) {
        w_cycle(a, actual, b, residual, error, num_grids, num_iterations);
    }
    test_grid_equality(expected_values, actual);
}


void run_cycle_tests() {

    // Size of the original (finest) grid
    const auto num_rows = std::pow(2, 8) + 1;
    const auto num_cols = std::pow(2, 8) + 1;
    
    auto num_grids = 5;
    auto num_cycles = 5;
    auto max_depth = 3;

    std::cout << "V/W-cycle tests: \n";
    // Solving Ix = b
    // Creating Identity matrix
    Grid a = Grid(num_rows, num_cols, 3);
    for (auto i = 0; i < num_rows; i++) { a[i*num_rows + i] = 1; }
    // Arbitrary LHS vector b
    Grid b = Grid(vector(num_rows, 7), max_depth);
    Grid residual = Grid(vector(num_rows, 0), max_depth);
    Grid error = Grid(vector(num_cols, 0), max_depth);
    Grid expected_values = Grid(vector(num_rows, 7), max_depth);
    test_v_cycle(a, b, residual, error, expected_values, num_grids, 10, num_cycles);
    test_w_cycle(a, b, residual, error, expected_values, num_grids, 10, num_cycles);

    // Solving small Ax = b
    max_depth = 2;
    a = Grid(vector{
        3, 2, 4, 2, 3,
        6, 6, 4, 1, 7,
        2, 1, 7, 3, 5,
        1, 0, 4, 4, 1,
        5, 3, 0, 2, 9,
    }, max_depth);
    b = Grid(vector{4, 5, 6, 3, 4}, max_depth);
    residual = Grid(vector(5, 0), max_depth);
    error = Grid(vector(5, 0), max_depth);
    // Verified with python numpy.linalg.solve()
    expected_values = Grid(vector{
        0.74,
        -0.56888889,
        0.59111111,
        -0.08666667,
        0.24222222,
    }, max_depth);
    test_v_cycle(a, b, residual, error, expected_values, 2, 20, num_cycles);
    test_w_cycle(a, b, residual, error, expected_values, 2, 20, num_cycles);

    // Solving larger Ax = b

}