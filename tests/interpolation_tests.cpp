#include <math.h>
#include <iostream>

#include "../includes/src_includes/printing.h"
#include "../includes/src_includes/interpolation.h"
#include "../includes/test_includes/interpolation_tests.h"


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
}
