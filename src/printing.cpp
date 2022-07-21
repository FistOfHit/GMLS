#include "../includes/src_includes/printing.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdio.h>
#include <string>
#include <vector>


using vector = std::vector<float>;


void print_matrix(const vector &matrix, const size_t num_rows,
    const int precision) {
	/* Print matrix element by element in easy to read manner.

	Notes
	-----
	Printing is done as expected, but to make the it a bit nicer, first the
    number of digits in each element is found and then we print it to 2 decimal
    places, so that each element is printed with the same amount of space
    around it. This keeps the printing clean and tidy, and avoids rows being
    offset when printing, making it much easier to see down columns.

	Parameters
	----------
	const std::vector<float> &matrix:
        The matrix to print
    const size_t num_rows:
        The number of rows in the matrix
    const int precision (default = 3):
        The numerical precision at which to print
	*/

	// Storing number of digits in each element
	std::vector<int> digits_matrix(num_rows * num_rows);

	// Find spaces required to print everything nicely
	size_t row_number;
	int num_digits, max_digits = 0;
	for (auto i = 0; i < num_rows; i++) {
		row_number = i * num_rows;

		for (auto j = 0; j < num_rows; j++) {
			num_digits = (int)std::log10(matrix[row_number + j]);
			max_digits = std::max(max_digits, num_digits);

			digits_matrix[row_number + j] = num_digits;
		}
	}

	// Size of whats being printed
	std::cout << std::setprecision(precision) << std::fixed;
	std::cout << "Matrix: " << num_rows << " X " << num_rows << "\n";
	std::cout << "[" << "\n";

	// Print row by row
	int num_spaces;
	for (auto i = 0; i < num_rows; i++) {
		row_number = i * num_rows;

		// Tidy brackets
		if (i == 0) { std::cout << "["; }
		else { std::cout << " ["; }

		// Print spaces for all but last element in each row
		for (auto j = 0; j < num_rows - 1; j++) {
			std::cout << matrix[row_number + j];

			// Print enough spaces to leave big enough gap
			num_spaces = max_digits - digits_matrix[row_number + j] + 1;
			for (auto k = 0; k < num_spaces; k++) {
                std::cout << " ";
            }
		}

		std::cout << matrix[row_number + num_rows - 1];

		// Tidy brackets
		if (i == num_rows - 1) { std::cout << "]]" << "\n"; }
		else { std::cout << "]" << "\n"; }
	}
}


void print_vector(const vector &vector, const int precision) {
	/* Print vector element by element in easy to read manner.

	Parameters
	----------
	const std::vector<float> &vector:
        The vector to print
    const int precision (default = 3):
        The numerical precision at which to print
	*/

	std::cout << std::setprecision(precision) << std::fixed;
	std::cout << "Vector: " << vector.size() << " elements" << "\n";

	std::cout << "[";
	for (auto i = 0; i < vector.size() - 1; i++) {
		std::cout << vector[i] << " ";
	}
	std::cout << vector[vector.size() - 1];
	std::cout << "]" << "\n";
}
