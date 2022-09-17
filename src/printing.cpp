#include "../include/printing.h"

#include "../include/grid.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>


void print_grid(const Grid &grid, const int precision) {

	// Storing number of digits in each element
	std::vector<int> digits_grid(grid.size());

    size_t num_rows = grid.num_rows();
    size_t num_cols = grid.num_cols();

	// Find spaces required to print everything nicely
	size_t row_number;
	int num_digits, max_digits = 0;
	for (auto i = 0; i < num_rows; i++) {
		row_number = i * num_cols;

		for (auto j = 0; j < num_cols; j++) {
			num_digits = (int)std::log10(grid[row_number + j]);
			max_digits = std::max(max_digits, num_digits);

			digits_grid[row_number + j] = num_digits;
		}
	}

	// Size of whats being printed
	std::cout << std::setprecision(precision) << std::fixed;
	std::cout << "Grid: " << num_rows << " X " << num_cols << "\n";
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
			std::cout << grid[row_number + j];

			// Print enough spaces to leave big enough gap
			num_spaces = max_digits - digits_grid[row_number + j] + 1;
			for (auto k = 0; k < num_spaces; k++) {
                std::cout << " ";
            }
		}

		std::cout << grid[row_number + num_cols - 1];

		// Tidy brackets
		if (i == num_rows - 1) { std::cout << "]]" << "\n"; }
		else { std::cout << "]" << "\n"; }
	}
}
