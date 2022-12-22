#include "tests/include/arithmetic_tests.h"
#include "tests/include/common.h"
#include "tests/include/multigrid_cycle_tests.h"
#include "tests/include/reshapers_tests.h"
#include "tests/include/smoothers_tests.h"
#include "tests/include/test_wrappers.h"

#include "include/grid.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>


void run_arithmetic_tests() {

    std::cout << "Vector-Vector addition/subtraction tests: \n";
    // 0 +- 0 = 0
    Grid<float> a = Grid<float>(5, 1);
    Grid<float> b = Grid<float>(5, 1);
    Grid<float> expected_values = Grid<float>(5, 1);
    test_add(a, b, expected_values);
    test_subtract(a, b, expected_values);

    // x +- 0 = x
    a = Grid<float>(std::vector<float>{1, 2, 3, 4, 5}, 1);
    b = Grid<float>(5, 1);
    expected_values = Grid<float>(std::vector<float>{1, 2, 3, 4, 5}, 1);;
    test_add(a, b, expected_values);
    test_subtract(a, b, expected_values);

    // 0 +- x = +-x
    a = Grid<float>(5, 1);
    b = Grid<float>(std::vector<float>{1, 2, 3, 4, 5}, 1);
    expected_values = Grid<float>(std::vector<float>{1, 2, 3, 4, 5}, 1);
    test_add(a, b, expected_values);
    expected_values = Grid<float>(std::vector<float>{-1, -2, -3, -4, -5}, 1);
    test_subtract(a, b, expected_values);

    // x - x = 0
    a = Grid<float>(std::vector<float>{1, 2, 3, 4, 5}, 1);
    b = Grid<float>(std::vector<float>{1, 2, 3, 4, 5}, 1);
    expected_values = Grid<float>(5, 0);
    test_subtract(a, b, expected_values);

    // x +- y = x +- y
    a = Grid<float>(std::vector<float>{1, 2, 3, 4, 5}, 1);
    b = Grid<float>(std::vector<float>{3, 3, 3, 3, 3}, 1);
    expected_values = Grid<float>(std::vector<float>{4, 5, 6, 7, 8}, 1);
    test_add(a, b, expected_values);
    expected_values = Grid<float>(std::vector<float>{-2, -1, 0, 1, 2}, 1);
    test_subtract(a, b, expected_values);

    std::cout << "Matrix-Vector multiplication tests: \n";
    const auto num_rows = 3;
    const auto num_cols = 3;
    // Diagonal matricies
    // 0 * 0 = 0
    a = Grid<float>(num_rows, num_cols, 1);
    b = Grid<float>(num_rows, 1);
    expected_values = Grid<float>(num_rows, 1);
    test_multiply(a, b, expected_values);

    // 0 * x = 0
    a = Grid<float>(num_rows, num_cols, 1);
    b = Grid<float>(num_rows, 1);
    expected_values = Grid<float>(num_rows, 1);
    test_multiply(a, b, expected_values);

    // x * 0 = 0
    a = Grid<float>(std::vector<float>{
        1, 0, 0,
        0, 1, 0,
        0, 0, 1,
    }, num_rows, num_cols, 1);
    b = Grid<float>(num_rows, 1);
    expected_values = Grid<float>(num_rows, 1);
    test_multiply(a, b, expected_values);

    // Next two tests also test reversibility of this transform
    // 1 * x = x
    a = Grid<float>(std::vector<float>{
        1, 0, 0,
        0, 1, 0,
        0, 0, 1,
    }, num_rows, num_cols, 1);
    b = Grid<float>(std::vector<float>{3, 3, 3}, 1);
    expected_values = Grid<float>(std::vector<float>{3, 3, 3}, 1);
    test_multiply(a, b, expected_values);

    // x * 1 = x
    a = Grid<float>(std::vector<float>{
        3, 0, 0,
        0, 3, 0,
        0, 0, 3,
    }, num_rows, num_cols, 1);
    b = Grid<float>(std::vector<float>{1, 1, 1}, 1);
    expected_values = Grid<float>(std::vector<float>{3, 3, 3}, 1);
    test_multiply(a, b, expected_values);

    // x * 1/x = 1
    a = Grid<float>(std::vector<float>{
        3, 0, 0,
        0, 3, 0,
        0, 0, 3,
    }, num_rows, num_cols, 1);
    b = Grid<float>({1.0F/3, 1.0F/3, 1.0F/3}, 1);
    expected_values = Grid<float>(std::vector<float>{1, 1, 1}, 1);
    test_multiply(a, b, expected_values);
    
    // Non-diagonal matricies
    // x * y = x * y
    a = Grid<float>(std::vector<float>{
        1, 2, 3,
        4, 5, 6,
        7, 8, 9,
    }, num_rows, num_cols, 1);
    b = Grid<float>(std::vector<float>{1, 2, 3}, 1);
    expected_values = Grid<float>(std::vector<float>{14, 32, 50}, 1);
    test_multiply(a, b, expected_values);
}


void run_cycle_tests() {

    std::cout << "V/W-cycle tests: \n";
    // Solving Ix = b
    auto num_cycles = 2;
    auto num_iterations = 2;
    auto num_rows = std::pow(2, 8) + 1;
    auto num_cols = std::pow(2, 8) + 1;
    auto max_depth = 3;

    // Creating Identity matrix
    Grid<float> a = Grid<float>(num_rows, num_cols, max_depth);
    for (auto i = 0; i < num_rows; i++) { a[i*num_rows + i] = 1; }

    // Arbitrary LHS vector b ( = 7)
    Grid<float> b = Grid<float>(std::vector<float>(num_rows, 7), max_depth);
    Grid<float> residual = Grid<float>(num_cols, max_depth);
    Grid<float> error = Grid<float>(num_rows, max_depth);
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

    residual = Grid<float>(num_cols, max_depth);
    error = Grid<float>(num_rows, max_depth);

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

    
}

void large_matrix_tests() {
    
    /// Solving larger Ax = b
    auto num_cycles = 20;
    auto num_iterations = 3;
    auto num_rows = 1025;
    auto num_cols = 1025;
    auto max_depth = 4;

    // SPD matrix formed from generating random A and getting A*(A^T)
    // Load A (LHS)
    std::fstream a_stream("../test_files/large_test_lhs.txt");
    std::string line;
    std::vector<double> a;
    std::cout << "a";
    while (std::getline(a_stream, line)) {
        float value;
        std::stringstream ss(line);
        std::cout << 1;
        while (ss >> value) {
            a.push_back(value);
        }
    }

    // std::vector<float> a = std::vector<float>(std::istream_iterator<float>(a_stream), std::istream_iterator<float>());
    // Grid<float> a = Grid<float>(
    //     std::vector<float>(a_start, a_end),
    //     num_rows,
    //     num_cols,
    //     max_depth);
    // std::vector<float> a = std::vector<float>(a_start, a_end);
    // std::cout << a.size() << std::endl;
    // std::cout << a[0] << std::endl;
    // std::cout << a[1] << std::endl;
    // std::cout << a[1024] << std::endl;

    // Load b (RHS)
    // std::ifstream b_stream("test_files/large_test_rhs.txt");
    // std::istream_iterator<float> b_start(b_stream), b_end;
    // Grid<float> b = Grid<float>(
    //     std::vector<float>(b_start, b_end),
    //     max_depth);
    
    // // Load x (expected solution)
    // std::ifstream x_stream("test_files/large_test_solution.txt");
    // std::istream_iterator<float> x_start(x_stream), x_end;
    // Grid<float> expected_values = Grid<float>(
    //     std::vector<float>(x_start, x_end),
    //     max_depth);
    
    // // Create residual and error grids
    // Grid<float> residual = Grid<float>(num_cols, max_depth);
    // Grid<float> error = Grid<float>(num_rows, max_depth);

    // test_v_cycle(a, b, residual, error, expected_values, num_iterations, num_cycles);
    // test_w_cycle(a, b, residual, error, expected_values, num_iterations, num_cycles);
}


void run_reshapers_tests() {

    std::cout << "Vector interpolation tests: \n";
    // Interpolating 0s - result should be 0
    Grid<float> coarse = Grid<float>(std::vector<float>(9, 0), 3);
    Grid<float> expected_values = Grid<float>(std::vector<float>(9, 0), 3);
    coarse.depth = 1;
    test_grid_interpolation(coarse, expected_values);
    
    // Interpolating from one grid level below
    coarse = Grid<float>(std::vector<float>{1, 0, 1, 0, 1, 0, 1, 0, 1}, 3);
    expected_values = Grid<float>(std::vector<float>(9, 1), 3);
    coarse.depth = 1;
    test_grid_interpolation(coarse, expected_values);

    // Interpolating from two grid levels below up to one grid level below
    coarse = Grid<float>(std::vector<float>{1, 0, 0, 0, 1, 0, 0, 0, 1}, 3);
    expected_values = Grid<float>(std::vector<float>{1, 0, 1, 0, 1, 0, 1, 0, 1}, 3);
    coarse.depth = 2;
    test_grid_interpolation(coarse, expected_values);

    // Interpolating a random vector
    coarse = Grid<float>(std::vector<float>{4, 2, 6, 8, 3, 5, 8, 1, 4}, 3);
    expected_values = Grid<float>(std::vector<float>{4, 5, 6, 4.5, 3, 5.5, 8, 6, 4}, 3);
    coarse.depth = 1;
    test_grid_interpolation(coarse, expected_values);

    std::cout << "Vector restriction tests: \n";
    // Restricting from one grid level above
    Grid<float> fine = Grid<float>(std::vector<float>(9, 1), 3);
    expected_values = Grid<float>(std::vector<float>(9, 1), 3);
    test_grid_restriction(fine, expected_values);

    // Restricting from one grid level above down to two grid levels below
    fine = Grid<float>(std::vector<float>{1, 0, 1, 0, 1, 0, 1, 0, 1}, 3);
    expected_values = Grid<float>(std::vector<float>{1, 0, 1, 0, 1, 0, 1, 0, 1}, 3);
    test_grid_restriction(fine, expected_values);

    // Restricting 0s - result should be 0
    fine = Grid<float>(std::vector<float>(9, 0), 3);
    expected_values = Grid<float>(std::vector<float>(9, 0), 3);
    test_grid_restriction(fine, expected_values);

    // Restricting a random vector
    coarse = Grid<float>(std::vector<float>{4, 2, 6, 8, 3, 5, 8, 1, 4}, 3);
    expected_values = Grid<float>(std::vector<float>{4, 2, 6, 8, 3, 5, 8, 1, 4}, 3);
    test_grid_restriction(coarse, expected_values);
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
