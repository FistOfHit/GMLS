#include <map>
#include <math.h>
#include <iostream>
#include "../includes/src_includes/printing.h"
#include "../includes/src_includes/reshapers.h"
#include "../includes/test_includes/common.h"
#include "../includes/test_includes/reshapers_tests.h"


using vector = std::vector<float>;


void test_vector_interpolation() {
	/* Test vector interpolation at various grid-depths.
	*/
    std::cout << "Vector interpolation correctness tests: \n";

	// Example coarse and fine arrays as they should be
	vector actual;
    std::map<int, vector> expecteds_map = std::map<int, vector>{
        {0, vector{1, 1.25, 1.5, 1.75, 2, 1.75, 1.5, 1.25, 1}},
        {1, vector{1, 0, 1.5, 0, 2, 0, 1.5, 0, 1}},
        {2, vector{1, 0, 0, 0, 2, 0, 0, 0, 1}},
    };

	// Test on multiple grid levels
    for (auto grid_depth = 2; grid_depth >= 1; grid_depth--) {
        actual = expecteds_map[grid_depth];
        interpolate_vector(actual, grid_depth);
        test_vector_equality(expecteds_map[grid_depth-1], actual);
    }

    actual = vector();
    expecteds_map = std::map<int, vector>();
}


void test_vector_restriction() {
    /* Test vector restriction at various grid-depths.
	*/
    std::cout << "Vector restriction correctness tests: \n";

	// Example coarse and fine arrays as they should be
	vector actual;
    std::map<int, vector> expecteds_map = std::map<int, vector>{
        {0, vector{1, 1.25, 1.5, 1.75, 2, 1.75, 1.5, 1.25, 1}},
        {1, vector{1, 1.25, 1.5, 1.75, 1.875, 1.75, 1.5, 1.25, 1}},
        {2, vector{1, 1.25, 1.5, 1.75, 1.6875, 1.75, 1.5, 1.25, 1}},
    };

	// Test on multiple grid levels
    const auto num_grids = 3;
    for (auto grid_depth = 0; grid_depth < num_grids - 1; grid_depth++) {
        actual = expecteds_map[grid_depth];
        restrict_vector(actual, grid_depth);
        test_vector_equality(expecteds_map[grid_depth+1], actual);
    }

    actual = vector();
    expecteds_map = std::map<int, vector>();
}


void test_reshapers() {
    test_vector_interpolation();
	test_vector_restriction();
}
