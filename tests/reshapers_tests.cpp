#include <math.h>
#include <iostream>

#include "../includes/src_includes/printing.h"
#include "../includes/src_includes/reshapers.h"
#include "../includes/test_includes/reshapers_tests.h"


void test_interpolation() {
	/* Checks whether or not interpolation function returns a valid
    interpolatied vector.

	Notes
	-----
	Performs a simple element by element check on an example vector generated
    by the current interpolation function in interpolation.cpp. Tolerance is
    defined manually here, not as input.
	*/
    std::cout << "Vector interpolation correctness test: ";

	// Example coarse and fine arrays as they should be
	std::vector<float> coarse_array = std::vector<float>{ 1, 1, 1 };
	std::vector<float> fine_array = std::vector<float>{ 0.5, 1, 1, 1, 1, 1, 0.5 };
	std::vector<float> fine_array_test = std::vector<float>(fine_array.size(), 0);

	// Write interpolated array into fine_array_test
	interpolate_vector(coarse_array, fine_array_test);

	// Compare element by element
	float tolerance = 10e-6;
	bool any_mismatch = false;
	for (auto i = 0; i < fine_array.size(); i++) {
		if (abs(fine_array[i] - fine_array_test[i]) > tolerance) {
			std::cout << "FAIL" << "\n";

            std::cout << "Expected output: " << "\n";
            print_vector(fine_array);
            std::cout << "Actual output:   " << "\n";
            print_vector(fine_array_test);
            return;
		}
	}

	std::cout << "PASS" << "\n";

    coarse_array = std::vector<float>();
    fine_array = std::vector<float>();
    fine_array_test = std::vector<float>();
}


void test_restriction() {
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


void test_reshapers() {
    test_interpolation()
	test_restriction();
}