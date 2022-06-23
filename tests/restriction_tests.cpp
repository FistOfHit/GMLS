#include <math.h>
#include <iostream>
#include <vector>

#include "../includes/src_includes/printing.h"
#include "../includes/src_includes/restriction.h"
#include "../includes/test_includes/restriction_tests.h"


void test_vec_restriction() {
	/* Checks whether or not vector restriction function returns a valid
    restricted vector.

	Notes
	-----
	Performs a simple element by element check on an example vector generated
    by the current restriction function in restriction.cpp. Tolerance is
    defined manually here, not as input.
	*/
    std::cout << "Vector restriction correctness test: ";

	// Example coarse and fine arrays as they should be
	const size_t fine_size = 7;
	const size_t coarse_size = 3;
	std::vector<float> fine_array(fine_size, 1);
	std::vector<float> coarse_array(coarse_size, 1);

	// Create and calculate with function
	std::vector<float> coarse_array_test(coarse_size, 0);
	restrict_vector(fine_array, coarse_array_test);

	// Compare element by element
	float tolerance = 10e-6;
	float difference;
	bool any_mismatch = false;
	for (auto i = 0; i < coarse_size; i++) {
		difference = abs(coarse_array[i] - coarse_array_test[i]);

		// If any element dosent match enough, fail test
		if (difference > tolerance) {
			std::cout << "FAIL" << "\n";

            std::cout << "Expected output: " << "\n";
            print_vector(coarse_array, 6);
            std::cout << "Actual output:   " << "\n";
            print_vector(coarse_array_test, 6);
            return;
		}
	}

	std::cout << "PASS" << "\n";

    coarse_array = std::vector<float>();
    coarse_array_test = std::vector<float>();
    fine_array = std::vector<float>();
}


void test_matrix_restriction() {
	/* Checks whether or not matrix restriction function works.

	Notes
	-----
	Performs a simple element by element check on an example matrix generated
    by the current restriction function in restriction.cpp. Tolerance is
    defined manually here, not as input.
	*/
    std::cout << "Matrix restriction correctness test: ";

	// 7 x 7 Matrix of 1s
    std::vector<float> fine_matrix(49, 1);

	// 3 x 3 Matrix of 1s
	std::vector<float> coarse_matrix(9, 1);

	// Create and calculate with function
	std::vector<float> coarse_matrix_test(9, 1);
	restrict_matrix(fine_matrix, 7, 7, coarse_matrix_test, 3, 3);

	// Compare element by element
	float tolerance = 10e-6;
	float difference;
	bool any_mismatch = false;
	for (auto i = 0; i < 9; i++) {
		difference = abs(coarse_matrix[i] - coarse_matrix_test[i]);

		// If any element dosent match, fail test
		if (difference > tolerance) {
			std::cout << "FAIL" << "\n";

            std::cout << "Expected output: " << "\n";
            print_matrix(coarse_matrix, 3, 3, 6);
            std::cout << "Actual output:   " << "\n";
            print_matrix(coarse_matrix_test, 3, 3, 6);
            return;
		}
	}

	std::cout << "PASS" << "\n";

    coarse_matrix = std::vector<float>();
    coarse_matrix_test = std::vector<float>();
    fine_matrix = std::vector<float>();
}


void test_restriction() {
	test_vec_restriction();
	test_matrix_restriction();
}
