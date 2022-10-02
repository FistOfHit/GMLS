#include "../include/common.h"
#include "../include/reshapers_tests.h"
#include "../../include/printing.h"
#include "../../include/reshapers.h"
#include <cmath>
#include <iostream>
#include <map>


using vector = std::vector<float>;


void test_grid_interpolation(const Grid &coarse, const Grid &expected_values) {

    Grid actual = Grid(coarse);

    coarse.depth++;
    interpolate_vector(actual);

    test_grid_equality(expected_values, actual);
}


void test_grid_restriction(const Grid &fine, const Grid &expected_values) {

    Grid actual = Grid(fine);

    fine.depth++;
    restrict_vector(actual);

    test_grid_equality(expected_values, actual);
}


void run_reshapers_tests() {

    std::cout << "Vector interpolation tests: \n";
    // Interpolating from one grid level below
    Grid coarse = Grid(vector{1, 0, 1, 0, 1, 0, 1, 0, 1}, 3);
    Grid expected_values = Grid(vector(9, 1), 3);
    test_grid_interpolation(coarse, expected_values);

    // Interpolating from two grid levels below up to one grid level below
    coarse = Grid(vector{1, 0, 0, 0, 1, 0, 0, 0, 1}, 3);
    expected_values = Grid(vector{1, 0, 1, 0, 1, 0, 1, 0, 1}, 3);
    test_grid_interpolation(coarse, expected_values);

    // Interpolating 0s - result should be 0
    coarse = Grid(vector(9, 0), 3);
    expected_values = Grid(vector(9, 0), 3);
    test_grid_interpolation(coarse, expected_values);

    // Interpolating a random vector
    coarse = Grid(vector{4, 2, 6, 8, 3, 5, 8, 1, 4}, 3);
    expected_values = Grid(vector{4, 5, 6, 4.5, 3, 5.5, 8, 6, 4}, 3);
    test_grid_interpolation(coarse, expected_values);

    std::cout << "Vector restriction tests: \n";
    // Restricting from one grid level above
    Grid fine = Grid(vector(9, 1), 3);
    expected_values = Grid(vector(9, 1), 3);
    test_grid_restriction(fine, expected_values);

    // Restricting from one grid level above down to two grid levels below
    fine = Grid(vector{1, 0, 1, 0, 1, 0, 1, 0, 1}, 3);
    expected_values = Grid(vector{1, 0, 1, 0, 1, 0, 1, 0, 1}, 3);
    test_grid_restriction(fine, expected_values);

    // Restricting 0s - result should be 0
    fine = Grid(vector(9, 0), 3);
    expected_values = Grid(vector(9, 0), 3);
    test_grid_restriction(fine, expected_values);

    // Restricting a random vector
    coarse = Grid(vector{4, 2, 6, 8, 3, 5, 8, 1, 4}, 3);
    expected_values = Grid(vector{4, 2, 6, 8, 3, 5, 8, 1, 4}, 3);
    test_grid_restriction(coarse, expected_values);
}
