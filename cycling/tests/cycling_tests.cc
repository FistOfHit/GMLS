#include "common/tests/common_tests.h"

#include "grid/grid.h"
#include "cycling/cycling.h"

#include <include/gtest/gtest.h>
#include <iostream>


void test_v_cycle(
    Grid<double>& lhs,
    Grid<double>& rhs,
    const Grid<double> expected_solution,
    const int num_iterations,
    const int num_cycles
) {
    // Construct residual and error from rhs/solution size
    auto residual = Grid<double>(rhs.num_rows(), rhs.max_depth());
    auto error = Grid<double>(
        expected_solution.num_rows(),
        expected_solution.max_depth()
    );

    auto actual_solution = Grid<double>(
        expected_solution.size(),
        expected_solution.max_depth()
    );

    for (auto i = 0; i < num_cycles; i++) {
        v_cycle(lhs, actual_solution, rhs, residual, error, num_iterations, 0);
    }

    test_grid_equality(expected_solution, actual_solution);
}


void test_w_cycle(
    Grid<double>& lhs,
    Grid<double>& rhs,
    const Grid<double> expected_solution,
    const int num_iterations,
    const int num_cycles
) {
    // Construct residual and error from rhs/solution size
    auto residual = Grid<double>(rhs.num_rows(), rhs.max_depth());
    auto error = Grid<double>(
        expected_solution.num_rows(),
        expected_solution.max_depth()
    );

    auto actual_solution = Grid<double>(
        expected_solution.size(),
        expected_solution.max_depth()
    );

    for (auto i = 0; i < num_cycles; i++) {
        w_cycle(lhs, actual_solution, rhs, residual, error, num_iterations);
    }

    test_grid_equality(expected_solution, actual_solution);
}


TEST(VCycleTests, SolvesIdentity) {

    // Solving Ix = b
    const auto num_rows = std::pow(2, 8) + 1;
    const auto num_cols = std::pow(2, 8) + 1;
    const auto max_depth = 3;
    const auto num_cycles = 2;
    const auto num_iterations = 2;

    // Creating Identity matrix
    auto identity_lhs = Grid<double>(num_rows, num_cols, max_depth);
    for (auto i = 0; i < num_rows; i++) { identity_lhs[i*num_rows + i] = 1; }

    // Arbitrary LHS vector b ( = 7), also the solution
    auto rhs = Grid<double>(std::vector<double>(num_rows, 7), max_depth);

    test_v_cycle(identity_lhs, rhs, rhs, num_iterations, num_cycles);
}


TEST(VCycleTests, RealTestCaseSmall) {

    // Solving small Ax = b
    const auto num_rows = 9;
    const auto num_cols = 9;
    const auto max_depth = 2;
    const auto num_cycles = 200;
    const auto num_iterations = 10;

    // SPD matrix formed from generating random A and getting A*(A^T)
    auto a = Grid<double>(
        std::vector<double>{
            385, 317, 310, 338, 237, 295, 265, 358, 200,
            317, 325, 261, 295, 226, 306, 238, 305, 204,
            310, 261, 284, 266, 184, 262, 207, 303, 170,
            338, 295, 266, 350, 201, 254, 226, 305, 190,
            237, 226, 184, 201, 249, 236, 249, 177, 152,
            295, 306, 262, 254, 236, 327, 240, 266, 197,
            265, 238, 207, 226, 249, 240, 285, 211, 176,
            358, 305, 303, 305, 177, 266, 211, 413, 192,
            200, 204, 170, 190, 152, 197, 176, 192, 157,
        },
        num_rows,
        num_cols,
        max_depth
    );

    auto b = Grid<double>(
        std::vector<double>{0, 2, 4, 5, 8, 8, 2, 6, 3,},
        max_depth
    );

    /// Verified with python numpy.linalg.solve()
    const auto expected_solution = Grid<double>(
        std::vector<double>{
            -0.67194828,
            -0.97521385,
            -0.28943875,
            0.60827349,
            0.33842962,
            0.74207787,
            -0.07373032,
            0.56177135,
            -0.14361974,
        },
        max_depth
    );

    test_v_cycle(a, b, expected_solution, num_iterations, num_cycles);
}


TEST(WCycleTests, SolvesIdentity) {

    // Solving Ix = b
    const auto num_rows = std::pow(2, 8) + 1;
    const auto num_cols = std::pow(2, 8) + 1;
    const auto max_depth = 3;
    const auto num_cycles = 2;
    const auto num_iterations = 2;

    // Creating Identity matrix
    auto identity_lhs = Grid<double>(num_rows, num_cols, max_depth);
    for (auto i = 0; i < num_rows; i++) { identity_lhs[i*num_rows + i] = 1; }

    // Arbitrary LHS vector b ( = 7), also the solution
    auto rhs = Grid<double>(std::vector<double>(num_rows, 7), max_depth);

    test_w_cycle(identity_lhs, rhs, rhs, num_iterations, num_cycles);
}


TEST(WCycleTests, RealTestCaseSmall) {

    // Solving small Ax = b
    const auto num_rows = 9;
    const auto num_cols = 9;
    const auto max_depth = 2;
    const auto num_cycles = 200;
    const auto num_iterations = 10;

    // SPD matrix formed from generating random A and getting A*(A^T)
    auto a = Grid<double>(
        std::vector<double>{
            385, 317, 310, 338, 237, 295, 265, 358, 200,
            317, 325, 261, 295, 226, 306, 238, 305, 204,
            310, 261, 284, 266, 184, 262, 207, 303, 170,
            338, 295, 266, 350, 201, 254, 226, 305, 190,
            237, 226, 184, 201, 249, 236, 249, 177, 152,
            295, 306, 262, 254, 236, 327, 240, 266, 197,
            265, 238, 207, 226, 249, 240, 285, 211, 176,
            358, 305, 303, 305, 177, 266, 211, 413, 192,
            200, 204, 170, 190, 152, 197, 176, 192, 157,
        },
        num_rows,
        num_cols,
        max_depth
    );

    auto b = Grid<double>(
        std::vector<double>{0, 2, 4, 5, 8, 8, 2, 6, 3,},
        max_depth
    );

    /// Verified with python numpy.linalg.solve()
    const auto expected_solution = Grid<double>(
        std::vector<double>{
            -0.67194828,
            -0.97521385,
            -0.28943875,
            0.60827349,
            0.33842962,
            0.74207787,
            -0.07373032,
            0.56177135,
            -0.14361974,
        },
        max_depth
    );

    test_w_cycle(a, b, expected_solution, num_iterations, num_cycles);
}


TEST(CyclingTests, RealTestCaseLarge) {

    /// Solving larger Ax = b
    // const auto num_cycles = 20;
    // const auto num_iterations = 3;
    // const auto num_rows = 1025;
    // const auto num_cols = 1025;
    // const auto max_depth = 4;

    // // SPD matrix formed from generating random A and getting A*(A^T)
    // // Load A (LHS)
    // std::fstream a_stream("../test_files/large_test_lhs.txt");
    // std::string line;
    // std::vector<double> a;
    // std::cout << "a";
    // while (std::getline(a_stream, line)) {
    //     float value;
    //     std::stringstream ss(line);
    //     std::cout << 1;
    //     while (ss >> value) {
    //         a.push_back(value);
    //     }
    // }

    // std::vector<double> a = std::vector<double>(std::istream_iterator<double>(a_stream), std::istream_iterator<double>());
    // Grid<double> a = Grid<double>(
    //     std::vector<double>(a_start, a_end),
    //     num_rows,
    //     num_cols,
    //     max_depth);
    // std::vector<double> a = std::vector<double>(a_start, a_end);
    // std::cout << a.size() << std::endl;
    // std::cout << a[0] << std::endl;
    // std::cout << a[1] << std::endl;
    // std::cout << a[1024] << std::endl;

    // Load b (RHS)
    // std::ifstream b_stream("test_files/large_test_rhs.txt");
    // std::istream_iterator<double> b_start(b_stream), b_end;
    // Grid<double> b = Grid<double>(
    //     std::vector<double>(b_start, b_end),
    //     max_depth);
    
    // // Load x (expected solution)
    // std::ifstream x_stream("test_files/large_test_solution.txt");
    // std::istream_iterator<double> x_start(x_stream), x_end;
    // Grid<double> expected_solution = Grid<double>(
    //     std::vector<double>(x_start, x_end),
    //     max_depth);

    // test_v_cycle(a, b, expected_solution, num_iterations, num_cycles);
    // test_w_cycle(a, b, expected_solution, num_iterations, num_cycles);
    ASSERT_TRUE(true);
}
