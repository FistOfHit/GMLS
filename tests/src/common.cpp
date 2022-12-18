#include "../include/common.h"
#include "../../include/grid.h"

#include <cmath>
#include <iostream>


void test_grid_equality(
    const Grid<float>& expected,
    const Grid<float>& actual,
    const float tolerance
) {
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


void log_failure(const Grid<float> &expected, const Grid<float> &actual) {

    auto precision = 10;

    std::cout << "FAIL" << "\n";
    std::cout << "\tExpected: " << "\n\t";
    expected.print(precision);
    std::cout << "\tActual:   " << "\n\t";
    actual.print(precision);
}
