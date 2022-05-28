#include "../includes/src_includes/interpolation.h"


void interpolate_vector(std::vector<float> coarse_array, std::vector<float> fine_array) {
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
	std::vector<int> coarse_array:
		Array of values for coarse version of vector

	std::vector<int> fine_array:
		Array of values for coarse version of vector
	*/

	// Special handling for end points
	fine_array[0] = 0.5 * coarse_array[0];
	fine_array[fine_array.size() - 1] = 0.5 * coarse_array[coarse_array.size() - 1];

	// Copying across odd-indexed elements
	for (auto i = 0; i < coarse_array.size(); i++) {
		fine_array[(i * 2) + 1] = coarse_array[i];
	}

	// Handling all the newly generated points
	for (auto i = 2; i < fine_array.size() - 2; i += 2) {
		fine_array[i] = 0.5 * (fine_array[i - 1] + fine_array[i + 1]);
	}
}
