#include <algorithm>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>


#include "../includes/src_includes/IO_routines.h"


using namespace std;


void read_matrix(double* matrix, int num_rows, int num_cols, string filename) {

	/* Read matrix from TXT file into pre-allocated memory.

	Notes
	-----

	Parameters
	----------
	double* matrix: pointer to array of doubles
		Matrix to be modified as per values read

	int num_rows: value greater than 0
		Number of rows in matrix

	int num_cols: value greater than 0
		Number of columns in matrix

	string filename:
		Name + path of TXT file from which to read

	Returns
	-------
	None
	*/



}


void write_matrix(double* matrix, int num_rows, int num_cols, string filename) {

	/* Write matrix from memory to TXT file.

	Notes
	-----

	Parameters
	----------
	double* matrix: pointer to array of doubles
		Matrix to write to file

	int num_rows: value greater than 0
		Number of rows in matrix

	int num_cols: value greater than 0
		Number of columns in matrix

	string filename:
		Name + path of TXT file to write to

	Returns
	-------
	None
	*/

}


void read_vector(double* vector, int size, string filename) {

	/* Read vector from TXT file into pre-allocated memory.

	Notes
	-----

	Parameters
	----------
	double* vector: pointer to array of doubles
		Vector to be modified as per values read

	int size: value greater than 0
		Number of elements in vector

	string filename:
		Name + path of TXT file from which to read

	Returns
	-------
	None
	*/

}


void write_vector(double* vector, int size, string filename) {

	/* Write vector from memory to TXT file.

	Notes
	-----

	Parameters
	----------
	double* vector: pointer to array of doubles
		Vector to write to file

	int size: value greater than 0
		Number of elements in vector

	string filename:
		Name + path of TXT file to be written into

	Returns
	-------
	None
	*/

}


void print_matrix(double* matrix, int num_rows, int num_cols, int precision) {

	/* Print matrix element by element in easy to read manner.

	Notes
	-----
	Printing is done as expected, but to make the it a bit
	nicer, first the number of digits in each element is
	found and then we print it to 2 decimal places, so that
	each element is printed with the same amount of space
	around it. This keeps the printing clean and tidy, and
	avoids rows being offset when printing, making it much
	easier to see down columns.

	Parameters
	----------
	double* matrix: pointer to array of doubles
		Matrix to be printed to screen

	int num_rows: value greater than 0
		Number of rows in matrix

	int num_cols: value greater than 0
		Number of columns in matrix

	Returns
	-------
	None
	*/

	// Storing number of digits in each element
	int* digits_matrix = new int[num_rows * num_cols];

	// Find spaces required to print everything nicely
	int row_number;
	int num_digits, max_digits = 0;
	for (int i = 0; i < num_rows; i++) {

		row_number = i * num_cols;

		for (int j = 0; j < num_cols; j++) {

			num_digits = (int)log10(matrix[row_number + j]);
			max_digits = max(max_digits, num_digits);

			digits_matrix[row_number + j] = num_digits;

		}

	}

	// Size of whats being printed
	cout << setprecision(precision) << fixed;
	cout << "Matrix: " << num_rows << " X " << num_cols << endl;
	cout << "[";

	// Print row by row
	int num_spaces;
	for (int i = 0; i < num_rows; i++) {

		row_number = i * num_cols;

		// Tidy brackets
		if (i == 0) {
			cout << "[";
		}
		else {
			cout << " [";
		}

		// Print spaces for all but last element in each row
		for (int j = 0; j < num_cols - 1; j++) {

			cout << matrix[row_number + j];

			// Print enough spaces to leave big enough gap
			num_spaces = max_digits - digits_matrix[row_number + j] + 1;
			for (int k = 0; k < num_spaces; k++) cout << " ";

		}

		cout << matrix[row_number + num_cols - 1];

		// Tidy brackets
		if (i == num_rows - 1) {
			cout << "]]" << endl;
		}
		else {
			cout << "]" << endl;
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

	Returns
	-------
	None
	*/

	// Size of whats being printed
	cout << setprecision(precision) << fixed;
	cout << "Vector: " << size << " elements" << endl;
	cout << "[";

	// Print row by row
	for (int i = 0; i < size - 1; i++) {
		cout << vector[i] << " ";
	}

	cout << vector[size - 1];

	cout << "]" << endl;

}
