#pragma once


void gs_smooth(double* lhs_matrix, int num_rows, int num_cols,
			   double* solution_vector, double* rhs_vector, 
			   double num_iterations);
void sor_smooth(double* lhs_matrix, int num_rows, int num_cols,
				double* solution_vector, double* rhs_vector,
				double num_iterations, double omega);
