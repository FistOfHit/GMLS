#include "../include/common.h"
#include "../include/smoothers_tests.h"
#include "../../include/printing.h"
#include "../../include/smoothers.h"
#include <cmath>
#include <iostream>
#include <vector>


using vector = std::vector<float>;
using map = std::vector<Grid>;


void test_smoothers(const Grid &test_matrix, const Grid &test_vector,
    const Grid &expected_values, const int num_iterations) {

    Grid actual = Grid(expected_values.size(), expected_values.max_depth());
    sor_smooth(test_matrix, actual, test_vector, num_iterations);
    test_grid_equality(expected_values, actual);

    actual = Grid(expected_values.size(), expected_values.max_depth());
    jacobi_smooth(test_matrix, actual, test_vector, num_iterations);
    test_grid_equality(expected_values, actual, 1e-3);
}


void run_smoother_tests() {
    
    std::cout << "Smoother correctness tests: \n";

    // Multiple grid levels
	// Ix = x
    size_t num_rows = 9;
    size_t num_cols = 9;
    int max_depth = 3;

    Grid test_matrix = Grid(vector(num_rows * num_cols, 0), num_rows, num_cols, max_depth);
    for (auto i = 0; i < num_rows; i++) { test_matrix[i*num_rows + i] = 1; }

    map test_grids_map = map{
        Grid(vector{3, 2, 1, 2, 3, 2, 1, 2, 3}, max_depth),
        Grid(vector{3, 0, 1, 0, 3, 0, 1, 0, 3}, max_depth),
        Grid(vector{3, 0, 0, 0, 3, 0, 0, 0, 3}, max_depth),
    };
    for (auto i = 0; i < 3; i++) {
        test_matrix.depth = i;
        test_smoothers(test_matrix, test_grids_map[i], test_grids_map[i]);
    }

    // Single grid level tests here on
    // 0 iterations result in a 0 solution vector (default initial value)
    Grid test_grid = Grid(vector(9, 0), 3);
    Grid expected_values = Grid(vector(9, 0), 3);
    test_smoothers(test_matrix, test_grid, expected_values, 0);

    // Ax = b
    num_rows = 5;
    num_cols = 5;
    test_matrix = Grid(vector{
        3, 2, 4, 2, 3,
        6, 6, 4, 1, 7,
        2, 1, 7, 3, 5,
        1, 0, 4, 4, 1,
        5, 3, 0, 2, 9,
    }, num_rows, num_cols, 1);
    test_grid = Grid(vector{4, 5, 6, 3, 4}, 1);
    // Verified with python numpy.linalg.solve()
    expected_values = Grid(vector{
        0.74,
        -0.56888889,
        0.59111111,
        -0.08666667,
        0.24222222,
    }, 1);
    test_smoothers(test_matrix, test_grid, expected_values);
}
