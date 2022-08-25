#include "../include/printing.h"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>


using vector = std::vector<float>;


void print_matrix(const vector &matrix, const size_t num_rows,
    const size_t num_cols, const int precision) {

	// Storing number of digits in each element
	std::vector<int> digits_matrix(num_rows * num_cols);

	// Find spaces required to print everything nicely
	size_t row_number;
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
		if (i == 0) { std::cout << "["; }
		else { std::cout << " ["; }

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
		if (i == num_rows - 1) { std::cout << "]]" << "\n"; }
		else { std::cout << "]" << "\n"; }
	}
}


void print_vector(const vector &vector, const int precision) {

	std::cout << std::setprecision(precision) << std::fixed;
	std::cout << "Vector: " << vector.size() << " elements" << "\n";

	std::cout << "[";
	for (auto i = 0; i < vector.size() - 1; i++) {
		std::cout << vector[i] << " ";
	}
	std::cout << vector[vector.size() - 1];
	std::cout << "]" << "\n";
}
