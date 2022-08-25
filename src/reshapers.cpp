#include "../include/reshapers.h"
#include <cmath>
#include <iostream>


using vector = std::vector<float>;


void interpolate_vector(vector &vector, const int grid_depth) {

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


void restrict_vector(vector &vector, const int grid_depth) {

    if (vector.size() == 3) {
        std::cout << "Attempting to restrict from coarsest possible grid level"
            << " (vector of size 3), exiting. \n";
        return;
    }
}


void restrict_matrix(vector &matrix, const int grid_depth) {}


void interpolate_matrix(vector &matrix, const int grid_depth) {}
