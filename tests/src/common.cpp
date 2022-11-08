#include "../include/common.h"
#include "../../include/grid.h"
#include "../../include/printing.h"

#include <cmath>
#include <iostream>


template <typename T>
void test_grid_equality(
    const Grid<T>& expected,
    const Grid<T>& actual,
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


template <typename T>
void log_failure(const Grid<T> &expected, const Grid<T> &actual) {

    std::cout << "FAIL" << "\n";
    std::cout << "\tExpected: " << "\n\t";
    print_grid(expected, 10);
    std::cout << "\tActual:   " << "\n\t";
    print_grid(actual, 10);
}
