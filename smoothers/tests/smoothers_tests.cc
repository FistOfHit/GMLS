#include "common/tests/common_tests.h"

#include "grid/grid.h"
#include "smoothers/smoothers.h"

#include <include/gtest/gtest.h>
#include <iostream>
#include <vector>


void test_smoothers(
    const Grid<double>& lhs,
    const Grid<double>& rhs,
    const Grid<double>& expected_solution,
    const int num_iterations
) {
    auto actual_solution = Grid<double>(
        expected_solution.size(),
        expected_solution.max_depth()
    );
    sor_smooth(lhs, actual_solution, rhs, num_iterations);
    test_grid_equality(expected_solution, actual_solution);

    actual_solution = Grid<double>(
        expected_solution.size(),
        expected_solution.max_depth()
    );
    jacobi_smooth(lhs, actual_solution, rhs, num_iterations);
    test_grid_equality(expected_solution, actual_solution);
}


TEST(SmootherTests, HandlesZeroIterations) {

    const auto num_rows = 9;
    const auto num_cols = 9;
    const auto max_depth = 1;
    // Zero Iterations
    const auto num_iterations = 0;

    // Construct random matrix
    const auto random_lhs = Grid<double>(
        std::vector<double>{
            3, 2, 4, 2, 3,
            6, 6, 4, 1, 7,
            2, 1, 7, 3, 5,
            1, 0, 4, 4, 1,
            5, 3, 0, 2, 9,
        },
        num_rows,
        num_cols,
        max_depth
    );

    // 0 iterations result in a constant solution vector (default initial value)
    const auto rhs = Grid<double>(std::vector<double>(num_rows, 0), max_depth);
    const auto expected_solution = Grid<double>(
        std::vector<double>(num_rows, 0), 
        max_depth
    );

    test_smoothers(random_lhs, rhs, expected_solution, num_iterations);
}


TEST(SmootherTests, PreservesIdentity) {

    const auto num_rows = 9;
    const auto num_cols = 9;
    const auto max_depth = 1;
    const auto num_iterations = 50;

    // Construct Identity matrix
    auto identity_lhs = Grid<double>(
        std::vector<double>(num_rows * num_cols, 0),
        num_rows,
        num_cols,
        max_depth
    );
    for (auto i = 0; i < num_rows; i++) { identity_lhs[i*num_rows + i] = 1; }

    // Both the RHS (b) and the solution in this equation
    const auto rhs = Grid<double>(
        std::vector<double>{3, 2, 1, 2, 3, 2, 1, 2, 3},
        max_depth
    );

    test_smoothers(identity_lhs, rhs, rhs, num_iterations);
}


TEST(SmootherTests, MultiLevelSmoothing) {

    const auto num_rows = 9;
    const auto num_cols = 9;
    const auto max_depth = 2;
    const auto num_iterations = 50;

    // Construct Identity matrix
    auto lhs = Grid<double>(
        std::vector<double>(num_rows * num_cols, 0),
        num_rows,
        num_cols,
        max_depth
    );
    for (auto i = 0; i < num_rows; i++) { lhs[i*num_rows + i] = 1; }

    auto depth_0_result = Grid<double>(
        std::vector<double>{3, 2, 1, 2, 3, 2, 1, 2, 3},
        max_depth
    );
    depth_0_result.set_depth(0);
    test_smoothers(lhs, depth_0_result, depth_0_result, num_iterations);

    auto depth_1_result = Grid<double>(
        std::vector<double>{3, 0, 1, 0, 3, 0, 1, 0, 3},
        max_depth
    );
    depth_1_result.set_depth(1);
    test_smoothers(lhs, depth_1_result, depth_1_result, num_iterations);

    auto depth_2_result = Grid<double>(
        std::vector<double>{3, 0, 0, 0, 3, 0, 0, 0, 3},
        max_depth
    );
    depth_2_result.set_depth(2);
    test_smoothers(lhs, depth_2_result, depth_2_result, num_iterations);
}


TEST(SmootherTests, RealTestCaseSmall) {

    // Ax = b
    const auto num_rows = 5;
    const auto num_cols = 5;
    const auto max_depth = 1;
    const auto num_iterations = 200;

    const auto a = Grid<double>(
        std::vector<double>{
            3, 2, 4, 2, 3,
            6, 6, 4, 1, 7,
            2, 1, 7, 3, 5,
            1, 0, 4, 4, 1,
            5, 3, 0, 2, 9,
        },
        num_rows,
        num_cols,
        max_depth
    );
    const auto b = Grid<double>(std::vector<double>{4, 5, 6, 3, 4}, max_depth);

    // Verified with python numpy.linalg.solve()
    const auto expected_solution = Grid<double>(
        std::vector<double>{
            0.74,
            -0.56888889,
            0.59111111,
            -0.08666667,
            0.24222222,
        },
        max_depth
    );
    
    test_smoothers(a, b, expected_solution, num_iterations);
}
