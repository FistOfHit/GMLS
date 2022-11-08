#include "../include/common.h"
#include "../include/grid.h"
#include "../include/reshapers_tests.h"

#include "../../include/printing.h"
#include "../../include/reshapers.h"

#include <cmath>
#include <iostream>
#include <map>


template <typename T>
void test_grid_interpolation(
    const Grid<T>& coarse,
    const Grid<T>& expected_values
) {
    Grid<T> actual = coarse;

    interpolate_vector(actual);
    coarse.depth--;

    test_grid_equality(expected_values, actual);
}


template <typename T>
void test_grid_restriction(
    const Grid<T>& fine,
    const Grid<T>& expected_values
) {
    Grid<T> actual = fine;

    restrict_vector(actual);
    fine.depth++;

    test_grid_equality(expected_values, actual);
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
