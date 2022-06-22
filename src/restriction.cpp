#include <memory>
#include <vector>
#include "../includes/src_includes/restriction.h"


void restrict_vector(const std::vector<float> &fine_vector, std::vector<float> &coarse_vector) {
	/* Restrict vector inverse linearly from 2^n-1 elements to 2^(n-1)-1 elements.

	Notes
	-----
	Performs simple inverse linear restriction, taking a centre-heavy
	weighted aritmetic average for new elements generated in between
	old elements, using the following stencil:
							1 2 1 -> 1

	Parameters
	----------
	const vector<float> &fine_vector
        The fine-grain vector to be restricted into the coarse_vector
    vector<float> &coarse_vector
        The coarse-grain vector to be filled in from fine_vector
	*/

	// find index of heavier centre point
	int centre_index;
	for (auto i = 0; i < coarse_vector.size(); i++) {
		centre_index = (i * 2) + 1;
		coarse_vector[i] = \
            0.25 * (fine_vector[centre_index - 1] + fine_vector[centre_index + 1])
            + 0.5 * fine_vector[centre_index];
	}
}


void restrict_matrix(const std::vector<float> &fine_matrix, const int fine_rows, const int fine_cols, std::vector<float> &coarse_matrix, const int coarse_rows, const int coarse_cols) {
	/* Restrict matrix from (2^n-1) x (2^n-1) elements to (2^(n-1)-1) x (2^(n-1)-1) elements.

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
    const int fine_rows:
        The number of rows in the fine matrix
    const int fine_cols:
        The number of columns in the fine matrix
    std::vector<float> &coarse_matrix:
        The coarse-grain matrix to be filled in from the fine_matrix
    const int coarse_rows:
        The number of rows in the coarse matrix
    const int coarse_cols:
        The number of rows in the coarse matrix
	*/

	// find centre of stencil for each coarse element and keep clearer track of
    // which row and column needed
	int centre_row, centre_col, behind_col, front_col, upper_fine_row,
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
