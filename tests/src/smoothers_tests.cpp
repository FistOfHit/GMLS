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

    Grid actual = Grid(expected_values.size(), 3);
    sor_smooth(test_matrix, actual, test_vector, 0, num_iterations);
    test_grid_equality(expected_values, actual);

    actual = Grid(expected_values.size(), 3);
    jacobi_smooth(test_matrix, actual, test_vector, 0, num_iterations);
    test_grid_equality(expected_values, actual);
}


void run_smoother_tests() {

    map test_grids_map;
    map expected_values_map;
    
    std::cout << "Smoother correctness tests: \n";

    // Multiple grid levels
	// Ix = x
    Grid test_matrix = Grid(vector(9 * 9, 0), 3);
    for (auto i = 0; i < 9; i++) { test_matrix[i*9 + i] = 1; }
    test_grids_map = map{
        Grid(vector{3, 2, 1, 2, 3, 2, 1, 2, 3}, 3),
        Grid(vector{3, 0, 1, 0, 3, 0, 1, 0, 3}, 3),
        Grid(vector{3, 0, 0, 0, 3, 0, 0, 0, 3}, 3),
    };
    for (auto i = 0; i < 3; i++) {
        test_smoothers(test_matrix, test_grids_map[i], test_grids_map[i], i);
    }

    // Single grid level tests here on
    // 0 iterations result in a 0 solution vector (default initial value)
    Grid test_grid = Grid(vector(9, 0), 3);
    Grid expected_values = Grid(vector(9, 0), 3);
    test_smoothers(test_matrix, test_grid, expected_values, 0);

    // Ax = b
    test_matrix = Grid(vector{
        3, 2, 4, 2, 3,
        6, 6, 4, 1, 7,
        2, 1, 7, 3, 5,
        1, 0, 4, 4, 1,
        5, 3, 0, 2, 9,
    }, 3);
    test_grid = Grid(vector{4, 5, 6, 3, 4}, 1);
    // Verified with python numpy.linalg.solve()
    expected_values = Grid(vector{
        0.74,
        -0.56888889,
        0.59111111,
        -0.08666667,
        0.24222222,
    }, 1);
    test_smoothers(test_matrix, test_grid, expected_values, 100);
}
