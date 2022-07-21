#include "../includes/test_includes/common.h"
#include "../includes/test_includes/cycle_tests.h"
#include "../includes/src_includes/multigrid_cycles.h"
#include "../includes/src_includes/printing.h"
#include <iostream>
#include <math.h>
#include <vector>


using vector = std::vector<float>;


void test_v_cycle(vector &a, vector &b, vector &r, vector&e,
    const vector expected_values, const int num_grids,
    const int num_iterations, const int num_cycles) {
    /* Test multigrid V-cycling. */
    vector actual = vector(expected_values.size(), 0);
    for (auto i = 0; i < num_cycles; i++) {
        v_cycle(a, actual, b, r, e, num_grids, num_iterations);
    }
    test_vector_equality(expected_values, actual);

    actual = vector();
}


void test_w_cycle(vector &a, vector &b, vector &r, vector&e,
    const vector expected_values, const int num_grids,
    const int num_iterations, const int num_cycles) {
    /* Test multigrid W-cycling. */
    vector actual = vector(expected_values.size(), 0);
    for (auto i = 0; i < num_cycles; i++) {
        w_cycle(a, actual, b, r, e, num_grids, num_iterations);
    }
    test_vector_equality(expected_values, actual);

    actual = vector();
}


void run_cycle_tests() {
    /* Run all tests for multigrid cycle. */
    vector a;
    vector b;
    vector r;
    vector e;
    vector expected_values;

    // Size of the original (finest) grid
    const auto num_rows = std::pow(2, 8) + 1;
    
    auto num_grids = 5;
    auto num_cycles = 5;

    std::cout << "V-cycle tests: \n";
    // Solving Ix = b
    // Creating Identity matrix
    a = vector(num_rows * num_rows, 0);
    for (auto i = 0; i < num_rows; i++) { a[i*num_rows + i] = 1; }
    // Arbitrary LHS vector b
    b = vector(num_rows, 7);
    r = vector(num_rows, 0);
    e = vector(num_rows, 0);
    expected_values = vector(b);
    test_v_cycle(a, b, r, e, expected_values, num_grids, 10, num_cycles);

    // Solving small Ax = b
    a = vector{
        3, 2, 4, 2, 3,
        6, 6, 4, 1, 7,
        2, 1, 7, 3, 5,
        1, 0, 4, 4, 1,
        5, 3, 0, 2, 9,
    };
    b = vector{4, 5, 6, 3, 4};
    r = vector(5, 0);
    e = vector(5, 0);
    // Verified with python numpy.linalg.solve()
    expected_values = vector{
        0.74,
        -0.56888889,
        0.59111111,
        -0.08666667,
        0.24222222,
    };
    test_v_cycle(a, b, r, e, expected_values, 2, 20, 5);
}