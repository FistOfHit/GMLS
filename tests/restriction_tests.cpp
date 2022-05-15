#include <math.h>
#include <iostream>

#include "../includes/src_includes/IO_routines.h"
#include "../includes/src_includes/restriction.h"
#include "../includes/test_includes/restriction_tests.h"


void is_vec_restriction_correct() {
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
	double fine_array[fine_size] = { 1, 1, 1, 1, 1, 1, 1 };
	double true_coarse_array[coarse_size] = { 1, 1, 1 };

	// Create and calculate with function
	double made_coarse_array[coarse_size] = { 0 };
	restrict_vector(fine_array, made_coarse_array, coarse_size);

	// Compare element by element
	double tolerance = 10e-6;
	double difference;
	bool any_mismatch = false;
	for (auto i = 0; i < coarse_size; i++) {
		difference = abs(true_coarse_array[i] - made_coarse_array[i]);

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

		// Print expected
		std::cout << "Expected output: " << "\n";
		print_vector(true_coarse_array, coarse_size, 6);

		// Print reality
		std::cout << "Actual output:   " << "\n";
		print_vector(made_coarse_array, coarse_size, 6);

	}
	else {
		std::cout << "PASS" << "\n";
	}

}



void is_matrix_restriction_correct() {
	/* Checks whether or not matrix restriction function returns a valid
    restricted matrix.

	Notes
	-----
	Performs a simple element by element check on an example matrix generated
    by the current restriction function in restriction.cpp. Tolerance is
    defined manually here, not as input.
	*/

	// Example coarse and fine arrays as they should be
	const int fine_size = 7;
	const int coarse_size = 3;
	double fine_array[fine_size * fine_size] = { 1, 1, 1, 1, 1, 1, 1,
												 1, 1, 1, 1, 1, 1, 1,
												 1, 1, 1, 1, 1, 1, 1,
												 1, 1, 1, 1, 1, 1, 1,
												 1, 1, 1, 1, 1, 1, 1,
												 1, 1, 1, 1, 1, 1, 1,
												 1, 1, 1, 1, 1, 1, 1 };
	double true_coarse_array[coarse_size * coarse_size] = { 1, 1, 1,
															1, 1, 1,
															1, 1, 1 };

	// Create and calculate with function
	double made_coarse_array[coarse_size * coarse_size] = { 0 };
	restrict_matrix(fine_array, fine_size, made_coarse_array,
					coarse_size, coarse_size);

	// Compare element by element
	double tolerance = 10e-6;
	double difference;
	bool any_mismatch = false;
	for (auto i = 0; i < coarse_size * coarse_size; i++) {
		difference = abs(true_coarse_array[i] - made_coarse_array[i]);

		// If any element dosent match enough, fail test
		if (difference > tolerance) {
			any_mismatch = true;
			break;
		}
	}

	// Inform user of outcome
	std::cout << "Matrix restriction correctness test: ";
	if (any_mismatch) {

		std::cout << "FAIL" << "\n";

		// Print expected
		std::cout << "Expected output: " << "\n";
		print_matrix(true_coarse_array, coarse_size, coarse_size, 6);

		// Print reality
		std::cout << "Actual output:   " << "\n";
		print_matrix(made_coarse_array, coarse_size, coarse_size, 6);

	}
	else {
		std::cout << "PASS" << "\n";
	}

}


void run_restriction_tests() {

	is_vec_restriction_correct();
	is_matrix_restriction_correct();

}
