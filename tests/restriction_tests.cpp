#include <math.h>
#include <iostream>
#include <vector>

#include "../includes/src_includes/printing.h"
#include "../includes/src_includes/matrix.h"
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

	// Example coarse and fine arrays as they should be
	const int fine_size = 7;
	const int coarse_size = 3;
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
			any_mismatch = true;
			break;
		}
	}

	// Inform user of outcome
	std::cout << "Vector restriction correctness test: ";
	if (any_mismatch) {
		std::cout << "FAIL" << "\n";

		std::cout << "Expected output: " << "\n";
		print_vector(coarse_array, 6);
		std::cout << "Actual output:   " << "\n";
		print_vector(coarse_array_test, 6);

	}
	else {
		std::cout << "PASS" << "\n";
	}

}


void test_matrix_restriction() {
	/* Checks whether or not matrix restriction function works.

	Notes
	-----
	Performs a simple element by element check on an example matrix generated
    by the current restriction function in restriction.cpp. Tolerance is
    defined manually here, not as input.
	*/

	// 7 x 7 Matrix of 1s
    std::vector<float> fine_values(49, 1);
    Matrix<float> fine_matrix = Matrix<float>(fine_values, 7, 7);

	// 3 x 3 Matrix of 1s
	std::vector<float> coarse_values(9, 1);
    Matrix<float> coarse_matrix = Matrix<float>(coarse_values, 3, 3);

	// Create and calculate with function
	std::vector<float> coarse_values_test(9, 1);
    Matrix<float> coarse_matrix_test = Matrix<float>(coarse_values_test, 3, 3);
	restrict_matrix(fine_matrix, coarse_matrix_test);

	// Compare element by element
	float tolerance = 10e-6;
	float difference;
	bool any_mismatch = false;
	for (auto i = 0; i < 9; i++) {
		difference = abs(coarse_matrix.values[i] - coarse_matrix_test.values[i]);

		// If any element dosent match, fail test
		if (difference > tolerance) {
			any_mismatch = true;
			break;
		}
	}

	// Inform user of outcome
	std::cout << "Matrix restriction correctness test: ";
	if (any_mismatch) {
		std::cout << "FAIL" << "\n";

		std::cout << "Expected output: " << "\n";
		print_matrix(coarse_matrix, 6);
		std::cout << "Actual output:   " << "\n";
		print_matrix(coarse_matrix_test, 6);
	}
	else {
		std::cout << "PASS" << "\n";
	}
}


void test_restriction() {
	test_vec_restriction();
	test_matrix_restriction();
}
