#include "../includes/src_includes/reshapers.h"
#include <iostream>
#include <math.h>


void interpolate_vector(std::vector<float> &vector, int grid_depth) {
	/* Interpolate vector linearly from 2^n+1 elements to 2^(n+1)+1 elements.

	Notes
	-----
	Performs simple linear interpolation, copying elements for odd indexes but
    otherwise taking a simple aritmetic average for new elements generated in
    between, using the following stencil:
	A simple copy for odd indexed elements and edge elements:
        [1] -> [1]
	and a simple average for even indexed elements:
        0.5 [1, 1] -> [1]

    Practically, this means that every "new" element introduced by ~doubling
    the size of the vector is simply the arithmetic average of its neighbours. 

    Given the current depth at which this grid is at in the set of all grids
    from fine->coarse, (0 -> number of grids) this function finds out which set
    of values need to be interpolated into which other set using variable 
    striding across the vector.

	Parameters
	----------
	const std::vector<float> &vector:
		Vector to be interpolated
    int grid_depth:
        The depth at which this grid is in the fine->coarse stages of grids
	*/

    if (grid_depth == 0) {
        std::cout << "Attempting to interpolate from finest level, exiting. \n"; 
        return;
    }

    // Determine stride length across vector
    int half_stride = std::pow(2, grid_depth-1);
    int stride = half_stride * 2;

	// Interpolating all "new" points
	for (auto i = half_stride; i <= vector.size() - half_stride; i += stride) {
		vector[i] = 0.5 * (vector[i - half_stride] + vector[i + half_stride]);
	}
}


void restrict_vector(std::vector<float> &vector, int grid_depth) {
	/* Restrict vector inverse linearly from 2^n+1 elements to 2^(n-1)+1 elements.

	Notes
	-----
	Performs simple inverse linear restriction, taking a centre-heavy
	weighted aritmetic average for new elements generated in between
	old elements, using the following stencil:
    A simple copy for odd indexed elements and edge elements:
        [1] -> [1]
    0.25 * [1, 2, 1] -> [1]

	Parameters
	----------
	const std::vector<float> &vector:
		Vector to be restricted
    int grid_depth:
        The depth at which this grid is in the fine->coarse stages of grids
	*/

    // Determine stride length across vector
    int half_stride = std::pow(2, grid_depth);
    int stride = half_stride * 2;

	for (auto i = stride; i <= vector.size() - stride; i += stride) {
        vector[i] = 0.5 * vector[i] + 0.25 * (vector[i - half_stride] + vector[i + half_stride]);
	}
}