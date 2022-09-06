#include "../include/reshapers.h"

#include "../include/grid.h"

#include <cmath>
#include <iostream>


void interpolate_vector(Grid &vector) {

    if (vector.depth == 0) {
        std::cout << "Attempting to interpolate from finest level, exiting. \n"; 
        return;
    }

    // Determine half-stride length across vector for edges
    int half_stride = vector.stride() / 2;

	// Interpolating all "new" points
	for (auto i = half_stride; i <= vector.size() - half_stride; i += vector.stride()) {
		vector[i] = 0.5 * (vector[i - half_stride] + vector[i + half_stride]);
	}
}


void restrict_vector(Grid &vector) {

    if (vector.size() == 3) {
        std::cout << "Attempting to restrict from coarsest possible grid level"
            << " (vector of size 3), exiting. \n";
        return;
    }
}


void interpolate_matrix(Grid &matrix) {}


void restrict_matrix(Grid &matrix) {}
