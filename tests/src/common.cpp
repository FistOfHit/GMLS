#include "../include/common.h"
#include "../../include/printing.h"
#include <cmath>
#include <iostream>


using vector = std::vector<float>;


void test_vector_equality(const vector &expected, const vector &actual,
    const float tolerance) {

    if (expected.size() != actual.size()) {
        std::cout << "Size mismatch:" << "\n";
        log_failure(expected, actual);
        return;
    }

    for (auto i = 0; i < expected.size(); i++) {
        if (std::fabs(expected[i] - actual[i]) > tolerance ||
            std::isnan(actual[i])) 
        {
            log_failure(expected, actual);
            return;
        }
    }

    std::cout << "PASS" << "\n";
}


void log_failure(const vector &expected, const vector &actual) {

    std::cout << "FAIL" << "\n";
    std::cout << "\tExpected: " << "\n\t";
    print_vector(expected);
    std::cout << "\tActual:   " << "\n\t";
    print_vector(actual);
}