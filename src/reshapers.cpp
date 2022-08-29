#include "../include/reshapers.h"

#include "../include/grid.h"

#include <cmath>
#include <iostream>


void interpolate_vector(Grid &vector) {

    if (vector.depth == 0) {
        std::cout << "Attempting to interpolate from finest level, exiting. \n"; 
        return;
    }

    // Determine stride length across vector
    int half_stride = std::pow(2, vector.depth - 1);
    int stride = half_stride * 2;

	// Interpolating all "new" points
	for (auto i = half_stride; i <= vector.size() - half_stride; i += stride) {
		vector[i] = 0.5 * (vector[i - half_stride] + vector[i + half_stride]);
	}

    // Decrease depth after interpolation (going one level up)
    vector.depth -= 1;
}


void restrict_vector(Grid &vector, const int grid_depth) {

    if (vector.size() == 3) {
        std::cout << "Attempting to restrict from coarsest possible grid level"
            << " (vector of size 3), exiting. \n";
        return;
    }

    // Increase depth after restriction (going one level down)
    vector.depth += 1;
}


void interpolate_matrix(Grid &matrix) {
    // Decrease depth after interpolation (going one level up)
    matrix.depth -= 1;
}


void restrict_matrix(Grid &matrix) {
    // Increase depth after restriction (going one level down)
    matrix.depth += 1;
}
