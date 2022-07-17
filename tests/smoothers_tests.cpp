#include <math.h>
#include <map>
#include <iostream>
#include <vector>
#include "../includes/src_includes/printing.h"
#include "../includes/src_includes/smoothers.h"
#include "../includes/test_includes/common.h"
#include "../includes/test_includes/smoothers_tests.h"


using vector = std::vector<float>;
using map = std::map<int, vector>;


void test_smoothers(const vector &test_matrix, const vector &test_vector,
    const vector &expected_values, const int grid_depth,
    const int num_iterations) {
    /* Test smoothers. */

    vector actual = vector(expected_values.size(), 0);
    sor_smooth(test_matrix, actual, test_vector, 0, num_iterations);
    test_vector_equality(expected_values, actual);

    actual = vector(expected_values.size(), 0);
    jacobi_smooth(test_matrix, actual, test_vector, 0, num_iterations);
    test_vector_equality(expected_values, actual);

    actual = vector();
}


void run_smoother_tests() {
    /*  */
    const size_t num_rows = 5;
    const size_t num_cols = 5;

    vector test_matrix;
    vector test_vector;
    vector expected_values;
    map test_vectors_map;
    map expected_values_map;
    
    std::cout << "Smoother correctness tests: \n";

    // Multiple grid levels
	// Ix = x
    test_matrix = vector{
        1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1,
    };
    test_vectors_map = map{
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

    // 0x = x
    test_matrix = vector{
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
    };
    test_vector = vector{3, 2, 1, 2, 3};
    expected_values = vector(5, 0);
    test_smoothers(test_matrix, test_vector, expected_values);

    // Ax = b
    test_matrix = vector{
        3, 2, 4, 2, 3,
        6, 6, 4, 1, 7,
        2, 1, 7, 3, 5,
        1, 0, 4, 0, 1,
        5, 3, 0, 2, 9,
    };
    test_vector = vector{4, 5, 6, 3, 4};
    // Verified with python numpy.linalg.solve()
    expected_values = vector{
        0.58860759,
        -0.40506329,
        0.5443038,
        0.08227848,
        0.23417722
    };
    test_smoothers(test_matrix, test_vector, expected_values);

    // Ax = b, non square matrix
    test_matrix = vector{
        3, 2, 4, 2, 3,
        6, 6, 4, 1, 7,
        2, 1, 7, 3, 5,
    };
    test_vector = vector{4, 5, 6};
    // Verified with python numpy.linalg.lstsq()
    expected_values = vector{
        0.2278481,
        0.02151899,
        0.54135021,
        0.34008439,
        0.14261603
    };
    test_smoothers(test_matrix, test_vector, expected_values);

    test_matrix = vector();
    test_vector = vector();
    expected_values = vector();
    expected_values_map = map();
}
