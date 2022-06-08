#include <math.h>
#include <iostream>

#include "../includes/src_includes/matrix.h"
#include "../includes/src_includes/printing.h"
#include "../includes/src_includes/smoother.h"
#include "../includes/test_includes/smoother_tests.h"


void test_gs_smoother() {
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
	*/

	// Setting up LHS and RHS as simple system
	const int size = 5;
    std::vector<double> lhs_vector = std::vector<double>{
        5, 2, 1, 1, 0,
        2, 5, 1, 3, 2,
        1, 1, 5, 3, 2,
        1, 3, 3, 5, 1,
        0, 2, 2, 1, 5 };
	Matrix lhs_matrix = Matrix(lhs_vector, size, size);

	// Random RHS
	std::vector<double> rhs_vector = std::vector<double>{ 0, 3, 0, 4, 3 };

    // Setup solution vector and truth
	std::vector<double> solution_test = std::vector<double>(size, 0);
	std::vector<double> solution = std::vector<double>{
        0.223264, -0.761726, -1.455909, 1.863039, 1.114446 };

	// Perform smoother
	gs_smoother(lhs_matrix, solution_test, rhs_vector, 100);

	// Compare element by element
	double tolerance = 10e-6;
	double difference;
	bool any_mismatch = false;
	for (auto i = 0; i < size; i++) {
		difference = abs(solution[i] - solution_test[i]);

		// If any element dosent match, fail test
		if (difference > tolerance) {
			any_mismatch = true;
			break;
		}
	}

	// Inform user of outcome
	std::cout << "Gauss-seidel smoother correctness test: ";
	if (any_mismatch) {
		std::cout << "FAIL" << "\n";

		std::cout << "Expected output: " << "\n";
		print_vector(solution, 6);
		std::cout << "Actual output:   " << "\n";
		print_vector(solution_test, 6);
	}
	else {
		std::cout << "PASS" << "\n";
	}
}


void test_sor_smoother() {
	/* Tests Successive over relaxation smoother correctness with pre-defined
    setup.

	Notes
	-----
	Here we use a Symmetric positive-definite matrix for our LHS, meaning we
    are guarunteed a solution, even for a seemingly randomly generated RHS b.
    We use 100 iterations for our solver here to ensure that it converges
    (for a 5 x 5 matrix atleast) IF it is a valid solver, to avoid any
    misjusgement based on convergence speed.
	*/

	// Setting up LHS and RHS as simple system
	const int size = 5;
    std::vector<double> lhs_vector = std::vector<double>{
        5, 2, 1, 1, 0,
        2, 5, 1, 3, 2,
        1, 1, 5, 3, 2,
        1, 3, 3, 5, 1,
        0, 2, 2, 1, 5 };
	Matrix lhs_matrix = Matrix(lhs_vector, size, size);

	// Random RHS
	std::vector<double> rhs_vector = std::vector<double>{ 0, 3, 0, 4, 3 };

    // Setup solution vector and truth
	std::vector<double> solution_test = std::vector<double>(size, 0);
	std::vector<double> solution = std::vector<double>{
        0.223264, -0.761726, -1.455909, 1.863039, 1.114446 };

	// Perform smoother
	sor_smoother(lhs_matrix, solution_test, rhs_vector, 100, 1.5);

	// Compare element by element
	double tolerance = 10e-6;
	double difference;
	bool any_mismatch = false;
	for (auto i = 0; i < size; i++) {

		difference = abs(solution[i] - solution_test[i]);

		// If any element dosent match, fail test
		if (difference > tolerance) {
			any_mismatch = true;
			break;
		}

	}

	std::cout << "SOR smoother correctness test: ";
	if (any_mismatch) {
		std::cout << "FAIL" << "\n";

		std::cout << "Expected output: " << "\n";
		print_vector(solution, 6);
		std::cout << "Actual output:   " << "\n";
		print_vector(solution_test, 6);
	}
	else {
		std::cout << "PASS" << "\n";
	}
}


void test_smoothers() {
	test_gs_smoother();
	test_sor_smoother();
}
