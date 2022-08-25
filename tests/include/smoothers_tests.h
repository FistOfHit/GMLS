#ifndef SMOOTHERS_TESTS_H
#define SMOOTHERS_TESTS_H
#endif

#include <vector>


using vector = std::vector<float>;


/* Test smoothers. */
void test_smoothers(const vector &test_matrix, const vector &test_vector,
    const vector &expected_values, const int grid_depth = 0,
    const int num_iterations = 100);


/* Run all smoother tests. */
void run_smoother_tests();
