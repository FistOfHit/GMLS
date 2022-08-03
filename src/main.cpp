#define TESTING_MODE 1

#ifdef TESTING_MODE
#include "../tests/includes/arithmetic_tests.h"
#include "../tests/includes/cycle_tests.h"
#include "../tests/includes/reshapers_tests.h"
#include "../tests/includes/smoothers_tests.h"
#endif

// Source includes
#include "../includes/multigrid_cycles.h"
#include "../includes/printing.h"
#include "../includes/reshapers.h"

#include <iostream>
#include <vector>


int main() {

    // Run all unit tests
    if (TESTING_MODE) {
        run_arithmetic_tests();
        run_cycle_tests();
        run_reshapers_tests();
        run_smoother_tests();
        return 0;
    }

	return 0;
}
