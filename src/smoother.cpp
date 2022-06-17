#include "../includes/src_includes/smoother.h"


void gs_smoother(Matrix<float> &lhs_matrix, std::vector<float> &solution_vector, const std::vector<float> &rhs_vector, const int num_iterations) {
	double row_sum;

	// Perform n Gauss-seidel SOR iterations
	for (auto n = 0; n < num_iterations; n++) {

		// Iterate through each element
		for (auto i = 0; i < lhs_matrix.num_rows; i++) {
			row_sum = 0;

			// Perform row-solution dot product
			for (auto j = 0; j < i; j++) {
				row_sum += lhs_matrix(i, j) * solution_vector[j];
			}

			// Careful with avoiding the i'th element
			for (auto j = i + 1; j < lhs_matrix.num_cols; j++) {
				row_sum += lhs_matrix(i, j) * solution_vector[j];
			}

			// Update solution vector
			solution_vector[i] = (rhs_vector[i] - row_sum) / lhs_matrix(i, i);
		}
	}
}


void sor_smoother(Matrix<float> &lhs_matrix, std::vector<float> &solution_vector, const std::vector<float> &rhs_vector, const int num_iterations, const int omega) {
	double row_sum;
	double new_solution;

	// Perform n Gauss-seidel SOR iterations
	for (auto n = 0; n < num_iterations; n++) {
		// Iterate through each element
		for (auto i = 0; i < lhs_matrix.num_rows; i++) {
			row_sum = 0;

			// Perform row-solution dot product
			for (auto j = 0; j < i; j++) {
				row_sum += lhs_matrix(i, j) * solution_vector[j];
			}
			// Careful with avoiding the i'th element
			for (auto j = i + 1; j < lhs_matrix.num_cols; j++) {
				row_sum += lhs_matrix(i, j) * solution_vector[j];
			}

			// Update solution vector
			new_solution = (rhs_vector[i] - row_sum) / lhs_matrix(i, i);
			solution_vector[i] = (omega * new_solution) + ((1 - omega) * solution_vector[i]);
		}
	}
}
