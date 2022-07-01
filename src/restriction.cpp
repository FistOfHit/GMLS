#include <math>
#include <memory>
#include <vector>
#include "../includes/src_includes/restriction.h"


void restrict_vector(std::vector<float> &vector, int grid_depth) {
	/* Restrict vector inverse linearly from 2^n+1 elements to 2^(n-1)+1 elements.

	Notes
	-----
	Performs simple inverse linear restriction, taking a centre-heavy
	weighted aritmetic average for new elements generated in between
	old elements, using the following stencil:
    A simple copy for odd indexed elements and edge elements:
        [1] -> [1]
    0.25 * [1, 2, 1] -> [1]

	Parameters
	----------
	const std::vector<float> &vector:
		Vector to be restricted
    int grid_depth:
        The depth at which this grid is in the fine->coarse stages of grids
	*/

    // Determine stride length across vector
    int half_stride = std::pow(2, grid_depth);
    int stride = half_stride * 2;

	for (auto i = stride; i <= vector.size() - stride; i += stride) {
        vector[i] = 0.5 * vector[i] + 0.25 * (vector[i - half_stride] + vector[i + half_stride]);
	}
}


void restrict_matrix(std::vector<float> &matrix, const size_t num_rows, const size_t num_cols) {
	/* Restrict matrix from (2^n+1) x (2^n+1) elements to (2^(n-1)+1) x (2^(n-1)+1) elements.

	Notes
	-----
	Performs full weighting restriction, taking a centre-heavy weighted
    aritmetic average for new elements generated in between old elements.
    Restriction stencil is in 2 dimensions, of the following pattern:

        1 2 1
        2 4 2 -> 1
        1 2 1

    The variables used here map as such:

                       behind_col: centre_col: front_col:
       upper_fine_row:      1           2           1                    j:
             fine_row:      2           4           2     -> coarse_row: 1
       lower_fine_row:      1           2           1

	Parameters
	----------
	const std::vector<float> &fine_matrix:
        The fine-grain matrix to be restricted into the coarse_matrix
    const size_t fine_rows:
        The number of rows in the fine matrix
    const size_t fine_cols:
        The number of columns in the fine matrix
    std::vector<float> &coarse_matrix:
        The coarse-grain matrix to be filled in from the fine_matrix
    const size_t coarse_rows:
        The number of rows in the coarse matrix
    const size_t coarse_cols:
        The number of rows in the coarse matrix
	*/

	// find centre of stencil for each coarse element and keep clearer track of
    // which row and column needed
	size_t centre_row, centre_col, behind_col, front_col, upper_fine_row,
        coarse_row, fine_row, lower_fine_row;

	for (auto i = 0; i < coarse_rows; i++) {
		// Set up row indexes
		coarse_row = i * coarse_cols;
		centre_row = (i * 2) + 1;
		fine_row = centre_row * fine_rows;
		upper_fine_row = fine_row - fine_rows;
		lower_fine_row = fine_row + fine_rows;

		for (auto j = 0; j < coarse_cols; j++) {
			// Set up column indexes
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
