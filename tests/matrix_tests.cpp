#include <iostream>
#include "../includes/src_includes/matrix.h"
#include "../includes/test_includes/matrix_tests.h"


void test_matrix_correctness(Matrix<float> &test_matrix, int num_rows, int num_cols) {
    /* Tests the correctness of a given, newly-initialised matrix.

    Parameters
    ----------
    Matrix<float> &test_matrix:
        The newly-initialised matrix to be testd
    int num_rows:
        The number of rows in this matrix
    int num_cols:
        The number of columns in this matrix
    */
    // Check matrix size
    if (test_matrix.num_rows != num_rows || test_matrix.num_cols != num_cols) {
        std::cout << "FAIL" << "\n";

		// Print expected and actual
		std::cout << "Expected matrix size: (" << num_rows << ", " << num_cols << ")\n";
		std::cout << "Actual matrix size:   (" << test_matrix.num_rows << ", " << test_matrix.num_cols << ")\n";
        return;
    }

    // Check every value is at the initial value
    for (auto i = 0; i < num_rows; i++) {
        for (auto j = 0; j < num_cols; j++) {
            if (test_matrix(i, j) != 0) {
                std::cout << "FAIL" << "\n";

                // Print expected and actual
                std::cout << "Expected value at (" << i << ", " << j << "): 0" << "\n";
                std::cout << "Actual value at   (" << i << ", " << j << "): " << test_matrix(i, j) << "\n";
                return;
            }
        }
    }

    std::cout << "PASS" << "\n";
}


void test_default_constructor() {
    std::cout << "Matrix constructor-by-value test: ";

    Matrix<float> test_matrix = Matrix<float>(5, 5);
    test_matrix_correctness(test_matrix, 5, 5);
}


void test_vector_constructor() {
    std::cout << "Matrix constructor-by-vector correctness test: ";

    std::vector<float> test_vector(5*5, 0);
    Matrix<float> test_matrix = Matrix<float>(test_vector, 5, 5);
    test_matrix_correctness(test_matrix, 5, 5);
}


void test_matrix() {
	test_default_constructor();
    test_vector_constructor();
}
