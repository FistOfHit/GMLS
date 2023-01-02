#include "common_tests.h"

#include "grid.h"

#include <include/gtest/gtest.h>
#include <iostream>


void test_grid_interpolation(
    const Grid<double>& coarse,
    const Grid<double>& expected_solution
) {
    auto actual = Grid<double>(coarse);

    actual.interpolate();
    actual.decrement_depth();

    test_grid_equality(expected_solution, actual);
}


void test_grid_restriction(
    const Grid<double>& fine,
    const Grid<double>& expected_solution
) {
    auto actual = Grid<double>(fine);

    actual.restrict();
    actual.increment_depth();

    test_grid_equality(expected_solution, actual);
}


TEST(InterpolationTests, PreservesZeros) {
    // Interpolating 0s - result should be 0
    auto coarse = Grid<double>(std::vector<double>(9, 0), 1);
    coarse.set_depth(1);
    const auto expected_solution = Grid<double>(std::vector<double>(9, 0), 1);
    test_grid_interpolation(coarse, expected_solution);
}


TEST(InterpolationTests, HandlesMultipleLevels) {
    // Interpolating from level 2 to 1
    auto coarse = Grid<double>(
        std::vector<double>{1, 0, 0, 0, 1, 0, 0, 0, 1},
        2
    );
    auto expected_solution = Grid<double>(
        std::vector<double>{1, 0, 1, 0, 1, 0, 1, 0, 1},
        2
    );
    coarse.set_depth(2);
    test_grid_interpolation(coarse, expected_solution);

    // Interpolating from level 1 to 0
    coarse = Grid<double>(
        std::vector<double>{1, 0, 1, 0, 1, 0, 1, 0, 1},
        1
    );
    expected_solution = Grid<double>(
        std::vector<double>{1, 1, 1, 1, 1, 1, 1, 1, 1},
        1
    );
    coarse.set_depth(1);
    test_grid_interpolation(coarse, expected_solution);
}


TEST(InterpolationTests, ResultCorrectnessTest) {
    // Interpolating a random vector
    auto coarse = Grid<double>(
        std::vector<double>{4, 2, 6, 8, 3, 5, 8, 1, 4},
        1
    );
    coarse.set_depth(1);
    const auto expected_solution = Grid<double>(
        std::vector<double>{4, 5, 6, 4.5, 3, 5.5, 8, 6, 4},
        1
    );

    test_grid_interpolation(coarse, expected_solution);
}


TEST(RestrictionTests, PreservesZeros) {
    // Restricting 0s - result should be 0
    const auto fine = Grid<double>(std::vector<double>(9, 0), 1);
    test_grid_restriction(fine, fine);
}


TEST(RestrictionTests, HandlesMultipleLevels) {
    // Restricting from level 0 to 1
    auto fine = Grid<double>(std::vector<double>(9, 1), 1);
    test_grid_restriction(fine, fine);

    // Further restricting from level 1 to 2
    fine = Grid<double>(std::vector<double>(9, 1), 2);
    test_grid_restriction(fine, fine);
}


TEST(RestrictionTests, ResultCorrectnessTest) {
    // Restricting a random vector
    const auto fine = Grid<double>(
        std::vector<double>{4, 2, 6, 8, 3, 5, 8, 1, 4},
        1
    );
    test_grid_restriction(fine, fine);
}
