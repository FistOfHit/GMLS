#include <math.h>


#include "../includes/src_includes/interpolation.h"


void interpolate_vector(std::vector<float> &vector, int grid_level) {
	/* Interpolate vector linearly from 2^n-1 elements to 2^(n+1)-1 elements.

	Notes
	-----
	Performs simple linear interpolation, copying elements for odd indexes but
    otherwise taking a simple aritmetic average for new elements generated in
    between, using the following stencil for the elements at either end of the
    vector:
        1 -> 0.5 0
	and the simple copy for odd indexed elements:
        1 -> 1
	and a simple average for even indexed elements:
        1 -> 0.5 0.5

	Parameters
	----------
	const std::vector<float> coarse_array:
		Array of values for coarse version of vector
	std::vector<float> fine_array:
		Array of values for coarse version of vector
	*/

    // Find sizes for coarse and fine grids
    size_t old_size = vector.size();
    int new_size_exponent = (int)std::log2(old_size + 1);
    size_t new_size = std::pow(2, new_size_exponent + 1) - 1;

	// Special handling for end points
	vector[0] = 0.5 * vector[1];
	vector[vector.size() - 1] = 0.5 * vector[vector.size() - 2];

	// Copying across odd-indexed elements
	for (auto i = 0; i < old_size; i++) {
		vector[(i * 2) + 1] = vector[i];
	}

	// Handling all the newly generated points
	for (auto i = 2; i < new_size - 2; i += 2) {
		vector[i] = 0.5 * (vector[i - 1] + vector[i + 1]);
	}
}
