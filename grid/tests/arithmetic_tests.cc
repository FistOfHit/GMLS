#include "common_tests.h"

#include "grid.h"

#include <include/gtest/gtest.h>
#include <iostream>


void test_add(
    const Grid<double>& a,
    const Grid<double>& b,
    const Grid<double>& expected_values
) {
    auto actual_solution = Grid<double>(a.size(), 0);
    actual_solution = a + b;
    test_grid_equality(expected_values, actual_solution);
}


void test_subtract(
    const Grid<double>& a,
    const Grid<double>& b,
    const Grid<double>& expected_values
) {
    auto actual_solution = Grid<double>(a.size(), 0);
    actual_solution = a - b;
    test_grid_equality(expected_values, actual_solution);
}


void test_multiply(
    const Grid<double>& matrix,
    const Grid<double>& vector,
    const Grid<double>& expected_values
) {
    auto actual_solution = Grid<double>(vector.size(), 0);
    actual_solution = matrix * vector;
    test_grid_equality(expected_values, actual_solution);
}


TEST(AddSubtractTests, TwoZeroesAreZero) {
    // 0 +- 0 = 0
    auto a = Grid<double>(5, 1);
    test_add(a, a, a);
    test_subtract(a, a, a);
}


TEST(AddSubtractTests, PreservesUnderZeroOperands) {
    // x -+ 0 = x
    auto a = Grid<double>(std::vector<double>{1, 2, 3, 4, 5}, 1);
    auto b = Grid<double>(5, 1);
    test_add(a, b, a);
    test_subtract(a, b, a);
}


TEST(AddSubtractTests, HandlesSignsCorrectly) {
    // 0 + x = x
    auto a = Grid<double>(5, 1);
    auto b = Grid<double>(std::vector<double>{1, 2, 3, 4, 5}, 1);
    test_add(a, b, b);

    // 0 - x = -x
    auto negative_a = Grid<double>(std::vector<double>{-1, -2, -3, -4, -5}, 1);
    test_subtract(a, b, negative_a);   
}


TEST(AddSubtractTests, CreatesZeroOnSelfSubtract) {
    // x - x = 0
    auto a = Grid<double>(std::vector<double>{1, 2, 3, 4, 5}, 1);
    auto expected_solution = Grid<double>(5, 0);
    test_subtract(a, a, expected_solution);
}


TEST(AddSubtractTests, ResultCorrectnessTest) {
    // x +- y = x +- y
    auto a = Grid<double>(std::vector<double>{1, 2, 3, 4, 5}, 1);
    auto b = Grid<double>(std::vector<double>{3, 3, 3, 3, 3}, 1);
    auto expected_solution = Grid<double>(
        std::vector<double>{4, 5, 6, 7, 8},
        1
    );
    test_add(a, b, expected_solution);

    expected_solution = Grid<double>(std::vector<double>{-2, -1, 0, 1, 2}, 1);
    test_subtract(a, b, expected_solution);
}


TEST(MultiplyTests, TwoZeroesAreZero) {
    // 0 * 0 = 0
    const auto a = Grid<double>(3, 3, 1);
    const auto b = Grid<double>(3, 1);
    const auto expected_solution = Grid<double>(3, 1);
    test_multiply(a, b, expected_solution);
}


TEST(MultiplyTests, CanMultiplyByZero) {
    // x * 0 = 0
    const auto a = Grid<double>(
        std::vector<double>{
            1, 0, 0,
            0, 1, 0,
            0, 0, 1,
        },
        3,
        3,
        1
    );
    const auto b = Grid<double>(3, 1);
    const auto expected_solution = Grid<double>(3, 1);
    test_multiply(a, b, expected_solution);
}


TEST(MultiplyTests, CanMultiplyByOne) {
    // x * 1 = x
    const auto a = Grid<double>(
        std::vector<double>{
            3, 0, 0,
            0, 3, 0,
            0, 0, 3,
        },
        3,
        3,
        1
    );
    const auto b = Grid<double>(std::vector<double>{1, 1, 1}, 1);
    const auto expected_solution = Grid<double>(std::vector<double>{3, 3, 3}, 1);
    test_multiply(a, b, expected_solution);
}


TEST(MultiplyTests, CanDivideByInversion) {
    // x * 1/x = 1
    const auto a = Grid<double>(
        std::vector<double>{
            3, 0, 0,
            0, 3, 0,
            0, 0, 3,
        },
        3,
        3,
        1
    );
    const auto b = Grid<double>({1.0F/3, 1.0F/3, 1.0F/3}, 1);
    const auto expected_solution = Grid<double>(std::vector<double>{1, 1, 1}, 1);
    test_multiply(a, b, expected_solution);
}


TEST(MultiplyTests, ResultCorrectnessTest) {
    // x * y = x * y
    const auto a = Grid<double>(
        std::vector<double>{
            1, 2, 3,
            4, 5, 6,
            7, 8, 9,
        },
        3,
        3,
        1
    );
    const auto b = Grid<double>(std::vector<double>{1, 2, 3}, 1);
    const auto expected_solution = Grid<double>(
        std::vector<double>{14, 32, 50},
        1
    );

    test_multiply(a, b, expected_solution);
}
