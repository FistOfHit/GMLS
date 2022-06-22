#include "../includes/src_includes/smoother.h"
#include <iostream>


void gs_smoother(const std::vector<float> &lhs_matrix, std::vector<float> &solution_vector, const std::vector<float> &rhs_vector, const int num_iterations) {
    /* Perform a given number of gauss-sidel smoothing iterations on a matrix.

    Notes
    -----

    Parameters
    ----------
    const std::vector<float> &lhs_matrix:
    std::vector<float> &solution_vector:
    const std::vector<float> &rhs_vector:
    const int num_iterations:
    */

    // Get matrix dimensions from equation vectors
    int num_rows = solution_vector.size();
    int num_cols = rhs_vector.size();

	// Perform n Gauss-seidel SOR iterations
    int row_num;
    double row_sum;
	for (auto n = 0; n < num_iterations; n++) {
		for (auto i = 0; i < num_rows; i++) {
            row_num = i * num_cols;
            row_sum = .0;

			// Perform row-solution dot product
			for (auto j = 0; j < i; j++) {
				row_sum += lhs_matrix[row_num + j] * solution_vector[j];
			}
			// Careful with avoiding the i'th element
			for (auto j = i + 1; j < num_cols; j++) {
				row_sum += lhs_matrix[row_num + j] * solution_vector[j];
			}

			// Update solution vector
			solution_vector[i] = (rhs_vector[i] - row_sum) / lhs_matrix[row_num + i];
		}
	}
}


void sor_smoother(const std::vector<float> &lhs_matrix, std::vector<float> &solution_vector, const std::vector<float> &rhs_vector, const int num_iterations, const int omega) {
    /* Perform a given number of SOR smoothing iterations on a matrix.

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
    int num_rows = solution_vector.size();
    int num_cols = rhs_vector.size();

	// Perform n Gauss-seidel SOR iterations
    int row_num;
    double row_sum, new_solution;
	for (auto n = 0; n < num_iterations; n++) {
		for (auto i = 0; i < num_rows; i++) {
			row_num = i * num_cols;
            row_sum = .0;

			// Perform row-solution dot product
			for (auto j = 0; j < i; j++) {
				row_sum += lhs_matrix[row_num + j] * solution_vector[j];
			}
			// Careful with avoiding the i'th element
			for (auto j = i + 1; j < num_cols; j++) {
				row_sum += lhs_matrix[row_num + j] * solution_vector[j];
			}

			// Update solution vector
			new_solution = (rhs_vector[i] - row_sum) / lhs_matrix[row_num + i];
			solution_vector[i] = (omega * new_solution) + ((1 - omega) * solution_vector[i]);
		}
	}
}
