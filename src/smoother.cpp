#include "../includes/src_includes/smoother.h"


void gs_smoother(double* lhs_matrix, int num_rows, int num_cols,
	double* solution_vector, double* rhs_vector, double num_iterations) {
	double row_sum;
	int row_index;

	// Perform n Gauss-seidel SOR iterations
	for (auto n = 0; n < num_iterations; n++) {

		// Iterate through each element
		for (auto i = 0; i < num_rows; i++) {
			row_sum = 0;
			row_index = i * num_cols;

			// Perform row-solution dot product
			for (auto j = 0; j < i; j++) {
				row_sum += lhs_matrix[row_index + j] * solution_vector[j];
			}

			// Careful with avoiding the i'th element
			for (auto j = i + 1; j < num_cols; j++) {
				row_sum += lhs_matrix[row_index + j] * solution_vector[j];
			}

			// Update solution vector
			solution_vector[i] = (rhs_vector[i] - row_sum) / lhs_matrix[row_index + i];
		}
	}
}


void sor_smoother(double* lhs_matrix, int num_rows, int num_cols,
    double* solution_vector, double* rhs_vector, double num_iterations,
    double omega) {
	double row_sum;
	int row_index;
	double new_solution;

	// Perform n Gauss-seidel SOR iterations
	for (auto n = 0; n < num_iterations; n++) {
		// Iterate through each element
		for (auto i = 0; i < num_rows; i++) {
			row_sum = 0;
			row_index = i * num_cols;

			// Perform row-solution dot product
			for (auto j = 0; j < i; j++) {
				row_sum += lhs_matrix[row_index + j] * solution_vector[j];
			}
			// Careful with avoiding the i'th element
			for (auto j = i + 1; j < num_cols; j++) {
				row_sum += lhs_matrix[row_index + j] * solution_vector[j];
			}

			// Update solution vector
			new_solution = (rhs_vector[i] - row_sum) / lhs_matrix[row_index + i];
			solution_vector[i] = (omega * new_solution) + ((1 - omega) * solution_vector[i]);
		}
	}
}
