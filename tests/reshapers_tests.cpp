#include <map>
#include <math.h>
#include <iostream>
#include "../includes/src_includes/printing.h"
#include "../includes/src_includes/reshapers.h"
#include "../includes/test_includes/common.h"
#include "../includes/test_includes/reshapers_tests.h"


using vector = std::vector<float>;


void test_vector_interpolation(const vector &coarse,
    const vector &expected_values, const int grid_depth) {
	/* Test vector interpolation. */
    vector actual = vector(coarse);
    interpolate_vector(actual, grid_depth);
    test_vector_equality(expected_values, actual);

    actual = vector();
}


void test_vector_restriction(const vector &fine, const vector &expected_values,
    const int grid_depth) {
    /* Test vector restriction. */
    vector actual = vector(fine);
    restrict_vector(actual, grid_depth);
    test_vector_equality(expected_values, actual);

    actual = vector();
}


void run_reshapers_tests() {
    /* Run all tests for reshape operators. */
    vector coarse;
    vector fine;
    vector expected_values;

    std::cout << "Vector interpolation tests: \n";
    // Interpolating from one grid level below
    coarse = vector{1, 0, 1, 0, 1, 0, 1, 0, 1};
    expected_values = vector(9, 1);
    test_vector_interpolation(coarse, expected_values, 1);

    // Interpolating from two grid levels below up to one grid level below
    coarse = vector{1, 0, 0, 0, 1, 0, 0, 0, 1};
    expected_values = vector{1, 0, 1, 0, 1, 0, 1, 0, 1};
    test_vector_interpolation(coarse, expected_values, 2);

    // Interpolating 0s - result should be 0
    coarse = vector(9, 0);
    expected_values = vector(9, 0);
    test_vector_interpolation(coarse, expected_values);

    // Interpolating a random vector
    coarse = vector{4, 2, 6, 8, 3, 5, 8, 1, 4};
    expected_values = vector{4, 5, 6, 4.5, 3, 5.5, 8, 6, 4};
    test_vector_interpolation(coarse, expected_values);

    std::cout << "Vector restriction tests: \n";
    // Restricting from one grid level above
    fine = vector(9, 1);
    expected_values = vector(9, 1);
    test_vector_restriction(fine, expected_values, 0);

    // Restricting from one grid level above down to two grid levels below
    fine = vector{1, 0, 1, 0, 1, 0, 1, 0, 1};
    expected_values = vector{1, 0, 1, 0, 1, 0, 1, 0, 1};
    test_vector_restriction(fine, expected_values, 1);

    // Restricting 0s - result should be 0
    fine = vector(9, 0);
    expected_values = vector(9, 0);
    test_vector_restriction(fine, expected_values);

    // Restricting a random vector
    coarse = vector{4, 2, 6, 8, 3, 5, 8, 1, 4};
    expected_values = vector{4, 2, 6, 8, 3, 5, 8, 1, 4};
    test_vector_restriction(coarse, expected_values);

    coarse = vector();
    fine = vector();
    expected_values = vector();
}
