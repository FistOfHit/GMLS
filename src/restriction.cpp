#include "../includes/src_includes/restriction.h"


void restrict_vector(double* fine_array, double* coarse_array, int coarse_size) {
	/* Restrict vector inverse linearly from 2^n-1 elements to 2^(n-1)-1 elements.

	Notes
	-----
	Performs simple inverse linear restriction, taking a centre-heavy
	weighted aritmetic average for new elements generated in between
	old elements, using the following stencil:
							1 2 1 -> 1

	Parameters
	----------
	double* fine_array: pointer to array of doubles
		Array of values for coarse version of vector

	int fine_size: Value greater than 0, a power of 2 + 1
		The size of the fine version of vector

	double* coarse_array: pointer to array of doubles
		Array of values for coarse version of vector

	int coarse_size: Value greater than 0, a power of 2 + 1
		The size of the coarse version of vector
	*/

	// find index of heavier centre point
	int centre_index;
	for (auto i = 0; i < coarse_size; i++) {
		centre_index = (i * 2) + 1;
		coarse_array[i] = \
            0.25 * (fine_array[centre_index - 1] + fine_array[centre_index + 1])
            + 0.5 * fine_array[centre_index];
	}
}


void restrict_matrix(double* fine_matrix, int num_fine_rows,
					 double* coarse_matrix, int num_coarse_rows,
                     int num_coarse_cols) {
	/* Restrict matrix from (2^n-1) x (2^n-1) elements to
    (2^(n-1)-1) x (2^(n-1)-1) elements.

	Notes
	-----
	Performs full weighting restriction, taking a centre-heavy weighted
    aritmetic average for new elements generated in between old elements.
    Restriction stencil is in 2 dimensions, of the following pattern:
        1 2 1
        2 4 2 -> 1
        1 2 1
	The actual implementation may seem a little sketchy, but a lot of it is
    just to reeduce the number of calculations needed to access and take the
    average of the arrays, making each matrix restriction a lot more efficient.

	Parameters
	----------
	double* fine_matrix: pointer to array of doubles
		Array of values for fine version of matrix

	int num_fine_rows: Value greater than 0, a power of 2 + 1
		The number of rows in the fine matrix

	double* coarse_matrix: pointer to array of doubles
		Array of values for coarse version of matrix

	int num_coarse_rows: Value greater than 0, a power of 2 + 1
		The number of rows in the coarse matrix

	int num_coarse_cols: Value greater than 0, a power of 2 + 1
		The number of columns in the coarse matrix
	*/

	// find centre of stencil for each coarse element and keep clearer track of
    // which row and column needed
	int centre_row, centre_col, behind_col, front_col, upper_fine_row,
        coarse_row, fine_row, lower_fine_row;

	for (auto i = 0; i < num_coarse_rows; i++) {
		// Set up row indexes for access
		coarse_row = i * num_coarse_cols;
		centre_row = (i * 2) + 1;
		fine_row = centre_row * num_fine_rows;
		upper_fine_row = fine_row - num_fine_rows;
		lower_fine_row = fine_row + num_fine_rows;

		for (auto j = 0; j < num_coarse_cols; j++) {
			// Set up column indexes for access
			centre_col = (j * 2) + 1;
			behind_col = centre_col - 1;
			front_col = centre_col + 1;

			coarse_matrix[coarse_row + j] = \
                // Corner points
                0.0625 * (fine_matrix[upper_fine_row + behind_col]
                        + fine_matrix[upper_fine_row + front_col]
                        + fine_matrix[lower_fine_row + front_col]
                        + fine_matrix[lower_fine_row + behind_col])
                // Side points
                + 0.125 * (fine_matrix[upper_fine_row + centre_col]
                        + fine_matrix[fine_row + behind_col]
                        + fine_matrix[fine_row + front_col]
                        + fine_matrix[lower_fine_row + centre_col])
                // Centre point
                + 0.25 * fine_matrix[fine_row + centre_col];
		}
	}
}
