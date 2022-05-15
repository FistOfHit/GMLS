#include <iostream>
#include <memory>
#include "../includes/src_includes/matrix.h"
#include "../includes/test_includes/matrix_tests.h"


void test_matrix_correctness(Matrix test_matrix, int num_rows, int num_cols, int initial_value) {
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
            if (test_matrix.values[i*test_matrix.num_cols + j] != initial_value) {
                std::cout << "FAIL" << "\n";

                // Print expected and actual
                std::cout << "Expected value at (" << i << ", " << j << "): " << initial_value << "\n";
                std::cout << "Actual value at   (" << i << ", " << j << "): " << test_matrix.values[i*test_matrix.num_cols + j] << "\n";
                return;
            }
        }
    }

    std::cout << "PASS" << "\n";
}


void test_value_constructor() {
    std::cout << "Matrix constructor-by-value test: ";

    std::unique_ptr<Matrix> test_matrix = std::make_unique<Matrix>(5, 5, 0);
    test_matrix_correctness(*test_matrix, 5, 5, 0);
}


void test_vector_constructor() {
    std::cout << "Matrix constructor-by-vector correctness test: ";

    std::vector<int> test_vector(5*5, 0);
    std::unique_ptr<Matrix> test_matrix = std::make_unique<Matrix>(test_vector, 5, 5);
    test_matrix_correctness(*test_matrix, 5, 5, 0);
}


void test_matrix() {
	test_value_constructor();
    test_vector_constructor();
}
