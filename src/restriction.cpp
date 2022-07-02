#include <math.h>
#include <memory>
#include <vector>
#include "../includes/src_includes/restriction.h"


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
