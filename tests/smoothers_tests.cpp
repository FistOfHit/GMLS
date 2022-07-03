#include <math.h>
#include <iostream>

#include "../includes/src_includes/printing.h"
#include "../includes/src_includes/smoothers.h"
#include "../includes/test_includes/smoothers_tests.h"



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
    std::cout << "SOR smoother correctness test: ";

	// Setting up LHS and RHS as simple system
	const size_t size = 5;
    std::vector<float> lhs_matrix = std::vector<float>{
        5, 2, 1, 1, 0,
        2, 5, 1, 3, 2,
        1, 1, 5, 3, 2,
        1, 3, 3, 5, 1,
        0, 2, 2, 1, 5 };

	// Random RHS
	std::vector<float> rhs_vector = std::vector<float>{ 0, 3, 0, 4, 3 };

    // Setup solution vector and truth
	std::vector<float> solution_test = std::vector<float>(size, 0);
	std::vector<float> solution = std::vector<float>{
        0.223264, -0.761726, -1.455909, 1.863039, 1.114446 };

	// Perform smoother
	sor_smooth(lhs_matrix, solution_test, rhs_vector, 100, 1.5);

	// Compare element by element
	double tolerance = 10e-6;
	double difference;
	for (auto i = 0; i < size; i++) {

		difference = abs(solution[i] - solution_test[i]);

		// If any element dosent match, fail test
		if (difference > tolerance) {
            std::cout << "FAIL" << "\n";

            std::cout << "\nExpected output: " << "\n";
            print_vector(solution, 6);
            std::cout << "\nActual output:   " << "\n";
            print_vector(solution_test, 6);
            return;
        }
	}

	std::cout << "PASS" << "\n";

    lhs_matrix = std::vector<float>();
    rhs_vector = std::vector<float>();
    solution = std::vector<float>();
    solution_test = std::vector<float>();
}


void test_jacbbi_smoother() {
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
    std::cout << "SOR smoother correctness test: ";

	// Setting up LHS and RHS as simple system
	const size_t size = 5;
    std::vector<float> lhs_matrix = std::vector<float>{
        5, 2, 1, 1, 0,
        2, 5, 1, 3, 2,
        1, 1, 5, 3, 2,
        1, 3, 3, 5, 1,
        0, 2, 2, 1, 5 };

	// Random RHS
	std::vector<float> rhs_vector = std::vector<float>{ 0, 3, 0, 4, 3 };

    // Setup solution vector and truth
	std::vector<float> solution_test = std::vector<float>(size, 0);
	std::vector<float> solution = std::vector<float>{
        0.223264, -0.761726, -1.455909, 1.863039, 1.114446 };

	// Perform smoother
	sor_smooth(lhs_matrix, solution_test, rhs_vector, 100, 1.5);

	// Compare element by element
	double tolerance = 10e-6;
	double difference;
	for (auto i = 0; i < size; i++) {

		difference = abs(solution[i] - solution_test[i]);

		// If any element dosent match, fail test
		if (difference > tolerance) {
            std::cout << "FAIL" << "\n";

            std::cout << "\nExpected output: " << "\n";
            print_vector(solution, 6);
            std::cout << "\nActual output:   " << "\n";
            print_vector(solution_test, 6);
            return;
        }
	}

	std::cout << "PASS" << "\n";

    lhs_matrix = std::vector<float>();
    rhs_vector = std::vector<float>();
    solution = std::vector<float>();
    solution_test = std::vector<float>();
}

void test_smoothers() {
	test_sor_smoother();
    test_jacobi_smoother();
}
