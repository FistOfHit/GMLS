#include "grid/grid.h"
#include "smoothers/smoothers.h"

#include <cmath>
#include <cstddef>
#include <iostream>


template <typename T>
void jacobi_smooth(
    const Grid<T>& a,
    Grid<T>& x,
    const Grid<T>& b,
    const int num_iterations,
    const float omega
) {
    // Create a duplicate solution vector x
    auto x_old = x;

	// Perform n iterations
    size_t row_num;
    float row_sum, new_solution;
	for (auto _ = 0; _ < num_iterations; _++) {
		for (auto i = 0; i < a.num_rows(); i += x.stride()) {
			row_num = i * a.num_cols();
            row_sum = .0F;

			// Perform row-solution dot product, avoiding i'th element
			for (auto j = 0; j < i; j += x.stride()) {
				row_sum += a[row_num + j] * x_old[j];
			}
			for (auto j = i + 1; j < a.num_cols(); j += x.stride()) {
				row_sum += a[row_num + j] * x_old[j];
			}

			// Update solution vector
			new_solution = (b[i] - row_sum) / a[row_num + i];
			x[i] = (omega * new_solution) + ((1 - omega) * x_old[i]);
		}

        // Replace x_old with the updated x
        x_old.move_elements_from(x);
	}
}


template <typename T>
void sor_smooth(
    const Grid<T>& a,
    Grid<T>& x,
    const Grid<T>& b,
    const int num_iterations,
    const float omega
) {
	// Perform n iterations
    size_t row_num;
    float row_sum, new_solution;

	for (auto _ = 0; _ < num_iterations; _++) {
		for (auto i = 0; i < a.num_rows(); i += x.stride()) {
			row_num = i * a.num_cols();
            row_sum = .0F;

			// Perform row-solution dot product, avoiding i'th element
			for (auto j = 0; j < i; j += x.stride()) {
				row_sum += a[row_num + j] * x[j];
			}
			for (auto j = i + 1; j < a.num_rows(); j += x.stride()) {
				row_sum += a[row_num + j] * x[j];
			}

			// Update solution vector
			new_solution = (b[i] - row_sum) / a[row_num + i];
			x[i] = (omega * new_solution) + ((1 - omega) * x[i]);
		}
	}
}


// Explicit instantiation
template void jacobi_smooth(
    const Grid<float>& a,
    Grid<float>& x,
    const Grid<float>& b,
    const int num_iterations,
    const float omega
);
template void jacobi_smooth(
    const Grid<double>& a,
    Grid<double>& x,
    const Grid<double>& b,
    const int num_iterations,
    const float omega
);

template void sor_smooth(
    const Grid<float>& a,
    Grid<float>& x,
    const Grid<float>& b,
    const int num_iterations,
    const float omega
);
template void sor_smooth(
    const Grid<double>& a,
    Grid<double>& x,
    const Grid<double>& b,
    const int num_iterations,
    const float omega
);
