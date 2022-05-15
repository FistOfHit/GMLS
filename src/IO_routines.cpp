#include <algorithm>
#include <math.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>


#include "../includes/src_includes/IO_routines.h"
#include "../includes/RapidCSV/rapidcsv.h"


void print_matrix(double* matrix, int num_rows, int num_cols, int precision) {
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
	double* matrix: pointer to array of doubles
		Matrix to be printed to screen

	int num_rows: value greater than 0
		Number of rows in matrix

	int num_cols: value greater than 0
		Number of columns in matrix
	*/

	// Storing number of digits in each element
	int* digits_matrix = new int[num_rows * num_cols];

	// Find spaces required to print everything nicely
	int row_number;
	int num_digits, max_digits = 0;
	for (auto i = 0; i < num_rows; i++) {
		row_number = i * num_cols;

		for (auto j = 0; j < num_cols; j++) {
			num_digits = (int)std::log10(matrix[row_number + j]);
			max_digits = std::max(max_digits, num_digits);

			digits_matrix[row_number + j] = num_digits;
		}
	}

	// Size of whats being printed
	std::cout << std::setprecision(precision) << std::fixed;
	std::cout << "Matrix: " << num_rows << " X " << num_cols << "\n";
	std::cout << "[" << "\n";

	// Print row by row
	int num_spaces;
	for (auto i = 0; i < num_rows; i++) {
		row_number = i * num_cols;

		// Tidy brackets
		if (i == 0) {
			std::cout << "[";
		}
		else {
			std::cout << " [";
		}

		// Print spaces for all but last element in each row
		for (auto j = 0; j < num_cols - 1; j++) {
			std::cout << matrix[row_number + j];

			// Print enough spaces to leave big enough gap
			num_spaces = max_digits - digits_matrix[row_number + j] + 1;
			for (auto k = 0; k < num_spaces; k++) {
                std::cout << " ";
            }
		}

		std::cout << matrix[row_number + num_cols - 1];

		// Tidy brackets
		if (i == num_rows - 1) {
			std::cout << "]]" << "\n";
		}
		else {
			std::cout << "]" << "\n";
		}
	}

	delete[] digits_matrix;
}


void print_vector(double* vector, int size, int precision) {
	/* Print vector element by element in easy to read manner.

	Notes
	-----

	Parameters
	----------
	double* vector: pointer to array of doubles
		Vector to be printed to screen

	int num_rows: value greater than 0
		Number of elements in vector
	*/

	// Size of whats being printed
	std::cout << std::setprecision(precision) << std::fixed;
	std::cout << "Vector: " << size << " elements" << "\n";
	std::cout << "[";

	// Print row by row
	for (auto i = 0; i < size - 1; i++) {
		std::cout << vector[i] << " ";
	}

	std::cout << vector[size - 1];
	std::cout << "]" << "\n";
}
