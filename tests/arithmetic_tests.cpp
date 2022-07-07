#include <algorithm>
#include <iostream>
#include <map>
#include <math.h>
#include <vector>
#include "../includes/src_includes/arithmetic.h"
#include "../includes/src_includes/printing.h"
#include "../includes/test_includes/arithmetic_tests.h"
#include "../includes/test_includes/common.h"


using vector = std::vector<float>;


void test_add() {
    /* Test vector addition at various grid depths.
    */
    std::cout << "Vector-Vector addition test: ";

    // Create test vectors for adding and storing actual
    vector test = vector{1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector expected = vector{2, 4, 6, 8, 10, 12, 14, 16, 18};
    vector actual;

    // Test on multiple grid levels
    int num_grids = 3;
    for (auto grid_depth = 0; grid_depth < num_grids; grid_depth++) {
        actual = vector(9, 0);
        add(test, test, grid_depth, actual);
        test_vector_equality(expected, actual);
    }

    test = vector();
    actual = vector();
    expected = vector();
}


void test_subtract() {
    /* Test vector subtraction at various grid depths.
    */
    std::cout << "Vector-Vector subtract test: ";

    // Create test vectors for adding and storing actual
    vector test_a = vector{1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector test_b = vector{9, 8, 7, 6, 5, 4, 3, 2, 1};
    vector expected = vector{-8, -6, -4, -2, 0, 2, 4, 6, 8};
    vector actual;

    // Test on multiple grid levels
    int num_grids = 3;
    for (auto grid_depth = 0; grid_depth < num_grids; grid_depth++) {
        actual = vector(9, 0);
        subtract(test_a, test_b, grid_depth, actual);
        test_vector_equality(expected, actual);
    }

    test_a = vector();
    test_b = vector();
    actual = vector();
    expected = vector();
}


void test_multiply() {
    /* Test vector subtraction at various grid depths.
    */
    std::cout << "Matrix-Vector multiplication test: ";

    // Create test vectors for adding and storing actual
    vector test_matrix = vector{
        1, 2, 3, 4, 5, 6, 7, 8, 9,
        1, 2, 3, 4, 5, 6, 7, 8, 9,
        1, 2, 3, 4, 5, 6, 7, 8, 9,
        1, 2, 3, 4, 5, 6, 7, 8, 9,
        1, 2, 3, 4, 5, 6, 7, 8, 9,
        1, 2, 3, 4, 5, 6, 7, 8, 9,
        1, 2, 3, 4, 5, 6, 7, 8, 9,
        1, 2, 3, 4, 5, 6, 7, 8, 9,
        1, 2, 3, 4, 5, 6, 7, 8, 9,
    };
    vector test_vector = vector{1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector actual;

    std::map<int, vector> expecteds_map = std::map<int, vector>{
        {0, vector{385, 385, 385, 385, 385, 385, 385, 385, 385}},
        {1, vector{165, 0, 165, 0, 165, 0, 165, 0, 165}},
        {2, vector{107, 0, 0, 0, 107, 0, 0, 0, 107}},
    };

    // Test on multiple grid levels
    int num_grids = 3;
    for (auto grid_depth = 0; grid_depth < num_grids; grid_depth++) {
        actual = vector(9, 0);
        multiply(test_matrix, 9, 9, test_vector, grid_depth, actual);
        test_vector_equality(expecteds_map[grid_depth], actual);
    }

    test_matrix = vector();
    actual = vector();
    expecteds_map = std::map<int, vector>();
}


void test_arithmetic() {
    test_add();
    test_subtract();
    test_multiply();
}