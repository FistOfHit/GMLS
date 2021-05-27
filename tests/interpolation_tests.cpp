#include <math.h>
#include <iostream>

#include "../includes/src_includes/IO_routines.h"
#include "../includes/src_includes/interpolation.h"
#include "../includes/test_includes/interpolation_tests.h"


using namespace std;


void is_interpolation_correct() {

	/* Checks whether or not interpolation function returns a
	valid interpolatied vector.

	Notes
	-----
	Performs a simple element by element check on an example vector
	generated by the current interpolation function in
	interpolation.cpp. Tolerance is defined manually here, not as
	input.

	Parameters
	----------
	None.

	Returns
	-------
	None.
	*/

	// Example coarse and fine arrays as they should be
	const int fine_size = 7;
	const int coarse_size = 3;
	double coarse_array[coarse_size] = { 1, 1, 1 };
	double true_fine_array[fine_size] = { 0.5, 1, 1, 1, 1, 1, 0.5 };

	// Create and calculate with function
	double made_fine_array[fine_size] = { 0 };
	interpolate_vector(coarse_array, coarse_size, made_fine_array, fine_size);

	// Compare element by element
	double tolerance = 10e-6;
	double difference;
	bool any_mismatch = false;
	for (int i = 0; i < fine_size; i++) {

		difference = abs(true_fine_array[i] - made_fine_array[i]);

		// If any element dosent match enough, fail test
		if (difference > tolerance) {
			any_mismatch = true;
			break;
		}

	}

	// Inform user of outcome
	cout << "Vector interpolation correctness test: ";
	if (any_mismatch) {

		cout << "FAIL" << endl;

		// Print expected
		cout << "Expected output: ";
		print_vector(true_fine_array, fine_size, 6);

		// Print reality
		cout << "Actual output:   ";
		print_vector(made_fine_array, fine_size, 6);

	}
	else {
		cout << "PASS" << endl;
	}

}


void run_interpolation_tests() {

	// Test if interpolation is working
	is_interpolation_correct();

}
