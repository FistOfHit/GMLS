#include <algorithm>
#include <iostream>
#include <math.h>
#include <vector>
#include "../includes/src_includes/arithmetic.h"
#include "../includes/src_includes/printing.h"
#include "../includes/test_includes/arithmetic_tests.h"


using vector = std::vector<float>;


void test_add() {
    /* Test vector addition at various grid depths.
    */

    // Create test vectors for adding and storing result
    vector test = vector{1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector result = vector(9, 0);
    vector ideal_result = vector{2, 4, 6, 8, 10, 12, 14, 16, 18};

    // Test on multiple grid levels
    int num_grids = 3;

    float tolerance = 10e-6;
	bool any_mismatch = false;
    for (auto grid_depth = 0; grid_depth < num_grids; grid_depth++) {
        
        // Determine stride length across vector/matrix
        int stride = std::pow(2, grid_depth);

        // Perform addition at this grid depth
        add(test, test, grid_depth, result);
        
        // Check that addition was done correctly.
        for (auto i = 0; i < result.size(); i += stride) {
            if (abs(result[i] - ideal_result[i]) > tolerance) {
                std::cout << "FAIL" << "\n";

                std::cout << "Expected output: " << "\n";
                print_vector(ideal_result);
                std::cout << "Actual output:   " << "\n";
                print_vector(result);
                return;
            }
        }
    }

    std::cout << "PASS" << "\n";

    test = vector();
    result = vector();
    ideal_result = vector();
}


void test_subtract() {
    /* Test vector subtraction at various grid depths.
    */

    // Create test vectors for adding and storing result
    vector test_a = vector{1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector test_b = vector{9, 8, 7, 6, 5, 4, 3, 2, 1};
    vector result = vector(9, 0);
    vector ideal_result = vector{-8, -6, -4, -2, 0, 2, 4, 6, 8};

    // Test on multiple grid levels
    int num_grids = 3;

    float tolerance = 10e-6;
	bool any_mismatch = false;
    for (auto grid_depth = 0; grid_depth < num_grids; grid_depth++) {
        
        // Determine stride length across vector/matrix
        int stride = std::pow(2, grid_depth);

        // Perform addition at this grid depth
        subtract(test_a, test_b, grid_depth, result);
        
        // Check that addition was done correctly.
        for (auto i = 0; i < result.size(); i += stride) {
            if (abs(result[i] - ideal_result[i]) > tolerance) {
                std::cout << "FAIL" << "\n";

                std::cout << "Expected output: " << "\n";
                print_vector(ideal_result);
                std::cout << "Actual output:   " << "\n";
                print_vector(result);
                return;
            }
        }
    }

    std::cout << "PASS" << "\n";

    test_a = vector();
    test_b = vector();
    result = vector();
    ideal_result = vector();
}


void test_multiply() {
    /* Test vector subtraction at various grid depths.
    */

    // Create test vectors for adding and storing result
    vector test_matrix = vector{
        1, 2, 3, 4, 5, 6, 7, 8, 9,
        1, 2, 3, 4, 5, 6, 7, 8, 9,
        1, 2, 3, 4, 5, 6, 7, 8, 9,
        1, 2, 3, 4, 5, 6, 7, 8, 9,
        1, 2, 3, 4, 5, 6, 7, 8, 9,
        1, 2, 3, 4, 5, 6, 7, 8, 9,
        1, 2, 3, 4, 5, 6, 7, 8, 9,
        1, 2, 3, 4, 5, 6, 7, 8, 9,
        1, 2, 3, 4, 5, 6, 7, 8, 9,
    };
    vector test_vector = vector{1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector result = vector(9, 0);

    vector ideal_result = vector{385, 385, 385, 385, 385, 385, 385, 385, 385};

    // Test on multiple grid levels
    int num_grids = 3;

    float tolerance = 10e-6;
	bool any_mismatch = false;
    for (auto grid_depth = 0; grid_depth < num_grids; grid_depth++) {
        
        // Determine stride length across vector/matrix
        int stride = std::pow(2, grid_depth);

        // Perform addition at this grid depth
        subtract(test, test, grid_depth, result);
        
        // Check that addition was done correctly.
        for (auto i = 0; i < result.size(); i += stride) {
            if (abs(result[i] - ideal_result[i]) > tolerance) {
                std::cout << "FAIL" << "\n";

                std::cout << "Expected output: " << "\n";
                print_vector(ideal_result);
                std::cout << "Actual output:   " << "\n";
                print_vector(result);
                return;
            }
        }
    }

    std::cout << "PASS" << "\n";

    test_a = vector();
    test_b = vector();
    result = vector();
    ideal_result = vector();
}