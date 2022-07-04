#include <algorithm>
#include <iostream>
#include <vector>
#include "../includes/src_includes/arithmetic.h"
#include "../includes/src_includes/printing.h"
#include "../includes/test_includes/arithmetic_tests.h"


using vector = std::vector<float>;


void test_add() {
    /*
    */

    // Create test vectors for adding and storing result
    vector test = vector{1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector result = vector(9, 0);
    vector ideal_result = vector{2, 4, 6, 8, 10, 12, 14, 16, 18};

    if (!std::equal(result.begin(), result.end(), ideal_result)) {
        std::cout << "FAIL" << "\n";

        std::cout << "Expected output: " << "\n";
        print_vector(ideal_result);
        std::cout << "Actual output:   " << "\n";
        print_vector(result);
        return;
    }

    std::cout << "PASS" << "\n";

    test = vector();
    result = vector();
    ideal_result = vector();
}


void test_subtract();


void test_multiply();