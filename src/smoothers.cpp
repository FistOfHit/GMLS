#include "../include/smoothers.h"
#include "../include/printing.h"
#include <cmath>
#include <cstddef>
#include <iostream>
#include <vector>


using vector = std::vector<float>;


void jacobi_smooth(const vector &a, vector &x, const vector &b,
    const int grid_depth, const int num_iterations, const float omega) {

    // Get matrix dimensions from equation vectors
    const auto num_rows = b.size();
    const auto num_cols = x.size();

    // Determine stride length across vector/matrix
    const auto stride = std::pow(2, grid_depth);

    // Create a duplicate solution vector x
    vector x_old = vector(x);

	// Perform n iterations
    size_t row_num;
    float row_sum, new_solution;
	for (auto _ = 0; _ < num_iterations; _++) {
		for (auto i = 0; i < num_rows; i += stride) {
			row_num = i * num_cols;
            row_sum = .0F;

			// Perform row-solution dot product, avoiding i'th element
			for (auto j = 0; j < i; j += stride) {
				row_sum += a[row_num + j] * x_old[j];
			}
			for (auto j = i + 1; j < num_cols; j += stride) {
				row_sum += a[row_num + j] * x_old[j];
			}

			// Update solution vector
			new_solution = (b[i] - row_sum) / a[row_num + i];
			x[i] = (omega * new_solution) + ((1 - omega) * x_old[i]);
		}

        // Replace x_old with the updated x
        x_old = vector(x);
	}
}


void sor_smooth(const vector &a, vector &x, const vector &b,
    const int grid_depth, const int num_iterations, const float omega) {

    // Get matrix dimensions from equation vectors
    const auto num_rows = b.size();
    const auto num_cols = x.size();

    // Determine stride length across vector/matrix
    const auto stride = std::pow(2, grid_depth);

	// Perform n iterations
    size_t row_num;
    float row_sum, new_solution;
	for (auto _ = 0; _ < num_iterations; _++) {
		for (auto i = 0; i < num_rows; i += stride) {
			row_num = i * num_cols;
            row_sum = .0F;

			// Perform row-solution dot product, avoiding i'th element
			for (auto j = 0; j < i; j += stride) {
				row_sum += a[row_num + j] * x[j];
			}
			for (auto j = i + 1; j < num_rows; j += stride) {
				row_sum += a[row_num + j] * x[j];
			}

			// Update solution vector
			new_solution = (b[i] - row_sum) / a[row_num + i];
			x[i] = (omega * new_solution) + ((1 - omega) * x[i]);
		}
	}
}
