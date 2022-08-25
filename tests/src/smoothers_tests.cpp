#include "../include/common.h"
#include "../include/smoothers_tests.h"
#include "../../include/printing.h"
#include "../../include/smoothers.h"
#include <cmath>
#include <iostream>
#include <map>
#include <vector>


using vector = std::vector<float>;
using map = std::map<int, vector>;


void test_smoothers(const vector &test_matrix, const vector &test_vector,
    const vector &expected_values, const int grid_depth,
    const int num_iterations) {

    vector actual = vector(expected_values.size(), 0);
    sor_smooth(test_matrix, actual, test_vector, 0, num_iterations);
    test_vector_equality(expected_values, actual);

    // actual = vector(expected_values.size(), 0);
    // // jacobi_smooth(test_matrix, actual, test_vector, 0, num_iterations);
    // test_vector_equality(expected_values, actual);

    actual = vector();
}


void run_smoother_tests() {

    vector test_matrix;
    vector test_vector;
    vector expected_values;
    map test_vectors_map;
    map expected_values_map;
    
    std::cout << "Smoother correctness tests: \n";

    // Multiple grid levels
	// Ix = x
    test_matrix = vector(9 * 9, 0);
    for (auto i = 0; i < 9; i++) { test_matrix[i*9 + i] = 1; }
    test_vectors_map = map{
        // cppcheck-suppress cppcheckError
        {0, vector{3, 2, 1, 2, 3, 2, 1, 2, 3}},
        {1, vector{3, 0, 1, 0, 3, 0, 1, 0, 3}},
        {2, vector{3, 0, 0, 0, 3, 0, 0, 0, 3}},
    };
    for (auto i = 0; i < 3; i++) {
        test_smoothers(test_matrix, test_vectors_map[i],
            test_vectors_map[i], i);
    }

    // Single grid level tests here on
    // 0 iterations result in a 0 solution vector (default initial value)
    expected_values = vector(9, 0);
    test_smoothers(test_matrix, test_vector, expected_values, 0, 0);

    // Ax = b
    test_matrix = vector{
        3, 2, 4, 2, 3,
        6, 6, 4, 1, 7,
        2, 1, 7, 3, 5,
        1, 0, 4, 4, 1,
        5, 3, 0, 2, 9,
    };
    test_vector = vector{4, 5, 6, 3, 4};
    // Verified with python numpy.linalg.solve()
    expected_values = vector{
        0.74,
        -0.56888889,
        0.59111111,
        -0.08666667,
        0.24222222,
    };
    test_smoothers(test_matrix, test_vector, expected_values, 0, 100);
}
