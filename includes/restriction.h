#pragma once


void restrict_vector(double* fine_array, double* coarse_array, int coarse_size);

void restrict_matrix(double* fine_matrix, int num_fine_rows,
					 double* coarse_matrix, int num_coarse_rows, int num_coarse_cols);
