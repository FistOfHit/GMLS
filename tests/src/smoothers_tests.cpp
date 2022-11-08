#include "../include/common.h"
#include "../include/smoothers_tests.h"

#include "../../include/printing.h"
#include "../../include/grid.h"
#include "../../include/smoothers.h"

#include <cmath>
#include <iostream>
#include <vector>


template <typename T>
void test_smoothers(num_iterations
    const Grid<T>& test_matrix,
    const Grid<T>& test_grid,
    const Grid<T>& expected_values,
    const int num_iterations
) {
    Grid<T> actual = Grid<T>(expected_values.size(), expected_values.max_depth());
    sor_smooth(test_matrix, actual, test_grid, num_iterations);
    test_grid_equality(expected_values, actual);

    actual = Grid<T>(expected_values.size(), expected_values.max_depth());
    jacobi_smooth(test_matrix, actual, test_vector, num_iterations);
    test_grid_equality(expected_values, actual, 1e-3);
}


void run_smoother_tests() {
    
    std::cout << "Smoother correctness tests: \n";

    // Multiple grid levels
	// Ix = x
    size_t num_rows = 9;
    size_t num_cols = 9;
    auto max_depth = 2;

    Grid<float> test_matrix = Grid<float>(std::vector<float>(num_rows * num_cols, 0), num_rows, num_cols, max_depth);
    for (auto i = 0; i < num_rows; i++) { test_matrix[i*num_rows + i] = 1; }

    auto depth_0_result = Grid<float>(std::vector<float>{3, 2, 1, 2, 3, 2, 1, 2, 3}, max_depth);
    depth_0_result.depth = 0;
    auto depth_1_result = Grid<float>(std::vector<float>{3, 0, 1, 0, 3, 0, 1, 0, 3}, max_depth);
    depth_1_result.depth = 1;
    auto depth_2_result = Grid<float>(std::vector<float>{3, 0, 0, 0, 3, 0, 0, 0, 3}, max_depth);
    depth_2_result.depth = 2;

    test_smoothers(test_matrix, depth_0_result, depth_0_result);
    test_smoothers(test_matrix, depth_1_result, depth_1_result);
    test_smoothers(test_matrix, depth_2_result, depth_2_result);

    // Single grid level tests here on
    // 0 iterations result in a 0 solution vector (default initial value)
    Grid<float> test_grid = Grid<float>(std::vector<float>(9, 0), 3);
    Grid<float> expected_values = Grid<float>(std::vector<float>(9, 0), 3);
    test_smoothers(test_matrix, test_grid, expected_values, 0);

    // Ax = b
    num_rows = 5;
    num_cols = 5;
    test_matrix = Grid<float>(std::vector<float>{
        3, 2, 4, 2, 3,
        6, 6, 4, 1, 7,
        2, 1, 7, 3, 5,
        1, 0, 4, 4, 1,
        5, 3, 0, 2, 9,
    }, num_rows, num_cols, 1);
    test_grid = Grid<float>(std::vector<float>{4, 5, 6, 3, 4}, 1);

    // Verified with python numpy.linalg.solve()
    expected_values = Grid<float>(std::vector<float>{
        0.74,
        -0.56888889,
        0.59111111,
        -0.08666667,
        0.24222222,
    }, 1);
    
    test_smoothers(test_matrix, test_grid, expected_values);
}
