#include "../includes/src_includes/smoothers.h"
#include "../includes/src_includes/printing.h"
#include <iostream>
#include <math.h>
#include <vector>


using vector = std::vector<float>;


void jacobi_smooth(const vector &a, vector &x, const vector &b,
    const int grid_depth, const int num_iterations, const float omega) {
    /* Perform a given number of Jacobi smoothing iterations on Ax=b.

    Notes
    -----
    Performs weighted Jacobi smoothing on a solution vector for a system 
    defined by Ax=b. The weighting factor Omega controls the proportion of the
    update that consists of the calculated solution and the previous value.
    The Jacobi algorithm does not require the latest solutions from the current
    timestep as they are calculated, and so at the cost of making a copy of the
    "old" solution or previous timestep, the update step can be paralellised to
    any degree.

    Parameters
    ----------
    const std::vector<float> &a:
        The LHS matrix A in Ax=b
    std::vector<float> &x:
        The solution vector x in Ax=b
    const std::vector<float> &b:
        The RHS vector b in Ax=b
    const int grid_depth:
        The depth at which this grid is in the fine->coarse stages of grids
    const int num_iterations:
        The number of iterations to apply the smoother for
    const int omega (default: 2.0F/3):
        The weighting factor Omega
    */

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
    /* Perform a given number of SOR smoothing iterations on Ax=b.

    Notes
    -----
    Performs weighted Sucessive Over-Relaxation (SOR) smoothing on a solution
    vector for a system defined by Ax=b. The weighting factor Omega controls
    the proportion of the update that consists of the calculated solution and
    the previous value. The SOR algorithm requires the latest solutions from
    the current timestep as they are calculated, and so the algorithm cannot
    be trivially paralellised. This implementation does not apply any
    paralellisation.

    Parameters
    ----------
    const std::vector<float> &a:
        The LHS matrix A in Ax=b
    std::vector<float> &x:
        The solution vector x in Ax=b
    const std::vector<float> &b:
        The RHS vector b in Ax=b
    const int grid_depth:
        The depth at which this grid is in the fine->coarse stages of grids
    const int num_iterations:
        The number of iterations to apply the smoother for
    const int omega (default: 1.0f):
        The weighting factor Omega
    */

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
