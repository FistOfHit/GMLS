#include <math.h>
#include <map>
#include <iostream>
#include <vector>
#include "../includes/src_includes/printing.h"
#include "../includes/src_includes/smoothers.h"
#include "../includes/test_includes/common.h"
#include "../includes/test_includes/smoothers_tests.h"


using vector = std::vector<float>;


void test_sor_smoother() {
    /* Test SOR smoothing at various grid-depths.
	*/
    std::cout << "SOR smoother correctness tests: \n";

	// Linear system setup
    vector test_matrix = vector{
        2, 1, 2, 1, 2, 1, 2, 1, 2,
        1, 2, 1, 2, 1, 2, 1, 2, 1,
        2, 1, 2, 1, 2, 1, 2, 1, 2,
        1, 2, 1, 2, 1, 2, 1, 2, 1,
        2, 1, 2, 1, 2, 1, 2, 1, 2,
        1, 2, 1, 2, 1, 2, 1, 2, 1,
        2, 1, 2, 1, 2, 1, 2, 1, 2,
        1, 2, 1, 2, 1, 2, 1, 2, 1,
        2, 1, 2, 1, 2, 1, 2, 1, 2,
    };
    vector test_vector = vector{3, 2, 1, 2, 3, 2, 1, 2, 3};
    
    // Example arrays as they should be post smoothing
	vector actual;
    std::map<int, vector> expecteds_map = std::map<int, vector>{
        {0, vector{1, 1.25, 1.5, 1.75, 2, 1.75, 1.5, 1.25, 1}},
        {1, vector{1, 0, 1.5, 0, 2, 0, 1.5, 0, 1}},
        {2, vector{1, 0, 0, 0, 2, 0, 0, 0, 1}},
    };

	// Test on multiple grid levels
    const auto num_grids = 3;
    for (auto grid_depth = 0; grid_depth < num_grids; grid_depth++) {
        actual = vector(9, 0);
        sor_smooth(test_matrix, actual, test_vector, grid_depth, 100, 1.5F);
        test_vector_equality(expecteds_map[grid_depth], actual);
    }

    actual = vector();
    expecteds_map = std::map<int, vector>();
    test_matrix = std::vector<float>();
    test_vector = std::vector<float>();
    actual = std::vector<float>();
}


void test_jacobi_smoother() {
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
    std::cout << "Jacobi smoother correctness tests: \n";

	// Linear system setup
    vector test_matrix = vector{
        2, 1, 2, 1, 2, 1, 2, 1, 2,
        1, 2, 1, 2, 1, 2, 1, 2, 1,
        2, 1, 2, 1, 2, 1, 2, 1, 2,
        1, 2, 1, 2, 1, 2, 1, 2, 1,
        2, 1, 2, 1, 2, 1, 2, 1, 2,
        1, 2, 1, 2, 1, 2, 1, 2, 1,
        2, 1, 2, 1, 2, 1, 2, 1, 2,
        1, 2, 1, 2, 1, 2, 1, 2, 1,
        2, 1, 2, 1, 2, 1, 2, 1, 2,
    };
    vector test_vector = vector{3, 2, 1, 2, 3, 2, 1, 2, 3};
    
    // Example arrays as they should be post smoothing
	vector actual;
    std::map<int, vector> expecteds_map = std::map<int, vector>{
        {0, vector{1, 1.25, 1.5, 1.75, 2, 1.75, 1.5, 1.25, 1}},
        {1, vector{1, 0, 1.5, 0, 2, 0, 1.5, 0, 1}},
        {2, vector{1, 0, 0, 0, 2, 0, 0, 0, 1}},
    };

	// Test on multiple grid levels
    const auto num_grids = 3;
    for (auto grid_depth = 0; grid_depth < num_grids; grid_depth++) {
        actual = vector(9, 0);
        jacobi_smooth(test_matrix, actual, test_vector, grid_depth, 100);
        test_vector_equality(expecteds_map[grid_depth], actual);
    }

    actual = vector();
    expecteds_map = std::map<int, vector>();
    test_matrix = std::vector<float>();
    test_vector = std::vector<float>();
    actual = std::vector<float>();
}

void test_smoothers() {
	test_sor_smoother();
    test_jacobi_smoother();
}
