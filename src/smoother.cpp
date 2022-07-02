#include "../includes/src_includes/smoother.h"
#include <iostream>
#include <math.h>


using vector = std::vector<float>;
void sor_smooth(const vector &a, vector &x, const vector &b, const int grid_depth, const int omega, const int num_iterations) {
    /* Perform a given number of SOR smoothing iterations on Ax=b.

    Notes
    -----

    Parameters
    ----------
    const std::vector<float> &lhs_matrix:
    std::vector<float> &solution_vector:
    const std::vector<float> &rhs_vector:
    const int num_iterations:
    const int omega:
    */

    // Get matrix dimensions from equation vectors
    size_t num_rows = x.size();
    size_t num_cols = b.size();

    // Determine stride length across vector/matrix
    int stride = std::pow(2, grid_depth);

	// Perform n Gauss-seidel SOR iterations
    size_t row_num;
    float row_sum, new_solution;
	for (auto _ = 0; _ < num_iterations; _++) {
		for (auto i = 0; i < num_rows; i += stride) {
			row_num = i * num_cols;
            row_sum = .0F;

			// Perform row-solution dot product
			for (auto j = 0; j < i; j += stride) {
				row_sum += a[row_num + j] * x[j];
			}
			// Careful with avoiding the i'th element
			for (auto j = i + 1; j < num_cols; j += stride) {
				row_sum += a[row_num + j] * x[j];
			}

			// Update solution vector
			new_solution = (b[i] - row_sum) / a[row_num + i];
			x[i] = (omega * new_solution) + ((1 - omega) * x[i]);
		}
	}
}


void jacobi_smooth(const vector &a, vector &x, const vector &b, const int grid_depth, const int num_iterations, const int omega) {
    /* Perform a given number of Jacobi smoothing iterations on Ax=b.

    Notes
    -----
    Requires a copy of the solution to avoid updating upon itself - 
    paralellism comes at the cost of memory and allocation

    Parameters
    ----------
    const std::vector<float> &lhs_matrix:
    std::vector<float> &solution_vector:
    const std::vector<float> &rhs_vector:
    const int num_iterations:
    const int omega:
    */

    // Get matrix dimensions from equation vectors
    size_t num_rows = x.size();
    size_t num_cols = b.size();

    // Determine stride length across vector/matrix
    int stride = std::pow(2, grid_depth);

    // Create a duplicate solution vector x
    vector x_old = vector(x);

	// Perform n Gauss-seidel SOR iterations
    size_t row_num;
    float row_sum, new_solution;
	for (auto _ = 0; _ < num_iterations; _++) {
		for (auto i = 0; i < num_rows; i += stride) {
			row_num = i * num_cols;
            row_sum = .0F;

			// Perform row-solution dot product
			for (auto j = 0; j < i; j += stride) {
				row_sum += a[row_num + j] * x_old[j];
			}
			// Careful with avoiding the i'th element
			for (auto j = i + 1; j < num_cols; j += stride) {
				row_sum += a[row_num + j] * x_old[j];
			}

			// Update solution vector
			new_solution = (b[i] - row_sum) / a[row_num + i];
			x[i] = (omega * new_solution) + ((1 - omega) * x_old[i]);
		}
	}
}