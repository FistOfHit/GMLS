#include <cmath>
#include <iostream>

#include "../includes/IO_routines.h"
#include "../includes/smoother.h"
#include "../includes/smoother_tests.h"


using namespace std;


void is_gssmooth_correct() {

	/* Tests Gauss-seidel smoother correctness with pre-defined setup.
	
	Notes
	-----
	Here we use a Symmetric positive-definite matrix for
	our LHS, meaning we are guarunteed a solution, even for
	a seemingly randomly generated RHS b. We use 100 
	iterations for our solver here to ensure that it
	converges (for a 5 x 5 matrix atleast) IF it is a valid
	solver, to avoid any misjusgement based on convergence
	speed. 

	Parameters
	----------
	None.

	Returns
	-------
	None.
	*/

	// Setting up LHS and RHS as simple system
	const int size = 5;
	double lhs_matrix[size  *size] = { 5, 2, 1, 1, 0,
									   2, 5, 1, 3, 2,
									   1, 1, 5, 3, 2,
									   1, 3, 3, 5, 1,
									   0, 2, 2, 1, 5 };
	// randomly generated RHS
	double rhs_vector[size] = { 0, 3, 0, 4, 3 };

	double made_solution[size] = { 0 };
	double true_solution[size] = { 0.223264, -0.761726, -1.455909, 1.863039, 1.114446 };

	// Perform smoother
	gs_smooth(lhs_matrix, size, size, made_solution, rhs_vector, 100);

	// Compare element by element
	double tolerance = 10e-6;
	double difference;
	bool any_mismatch = false;
	for (int i = 0; i < size; i++) {

		difference = abs(true_solution[i] - made_solution[i]);

		// If any element dosent match enough, fail test
		if (difference > tolerance) {
			any_mismatch = true;
			break;
		}

	}

	// Inform user of outcome
	cout << "Gauss-seidel smoother correctness test: ";
	if (any_mismatch) {

		cout << "FAIL" << endl;

		// Print expected 
		cout << "Expected output: ";
		print_vector(true_solution, size, 6);

		// Print reality
		cout << "Actual output:   ";
		print_vector(made_solution, size, 6);

	}
	else {
		cout << "PASS" << endl;
	}

}


void is_sorsmooth_correct() {

	/* Tests Successive over relaxation smoother correctness with
	pre-defined setup.

	Notes
	-----
	Here we use a Symmetric positive-definite matrix for
	our LHS, meaning we are guarunteed a solution, even for
	a seemingly randomly generated RHS b. We use 100 
	iterations for our solver here to ensure that it
	converges (for a 5 x 5 matrix atleast) IF it is a valid
	solver, to avoid any misjusgement based on convergence
	speed. 

	Parameters
	----------
	None.

	Returns
	-------
	None.
	*/

	// Setting up LHS and RHS as simple system
	const int size = 5;
	double lhs_matrix[size  *size] = { 5, 2, 1, 1, 0,
									   2, 5, 1, 3, 2,
									   1, 1, 5, 3, 2,
									   1, 3, 3, 5, 1,
									   0, 2, 2, 1, 5 };
	// randomly generated RHS
	double rhs_vector[size] = { 0, 3, 0, 4, 3 };

	double made_solution[size] = { 0 };
	double true_solution[size] = { 0.223264, -0.761726, -1.455909, 1.863039, 1.114446 };

	// Perform smoother
	sor_smooth(lhs_matrix, size, size, made_solution, rhs_vector, 100, 1.5);

	// Compare element by element
	double tolerance = 10e-6;
	double difference;
	bool any_mismatch = false;
	for (int i = 0; i < size; i++) {

		difference = abs(true_solution[i] - made_solution[i]);

		// If any element dosent match enough, fail test
		if (difference > tolerance) {
			any_mismatch = true;
			break;
		}

	}

	// Inform user of outcome
	cout << "SOR smoother correctness test: ";
	if (any_mismatch) {

		cout << "FAIL" << endl;

		// Print expected 
		cout << "Expected output: ";
		print_vector(true_solution, size, 6);

		// Print reality
		cout << "Actual output:   ";
		print_vector(made_solution, size, 6);

	}
	else {
		cout << "PASS" << endl;
	}

}


void run_smoother_tests() {

	// Check Gauss-seidel smoother
	is_gssmooth_correct();
	
	// Check SOR smoother
	is_sorsmooth_correct();

}
