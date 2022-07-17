#define TESTING_MODE 1

#ifdef TESTING_MODE
#include "../includes/test_includes/arithmetic_tests.h"
#include "../includes/test_includes/reshapers_tests.h"
#include "../includes/test_includes/smoothers_tests.h"
#endif

// Source includes
#include "../includes/src_includes/multigrid_cycles.h"
#include "../includes/src_includes/printing.h"
#include "../includes/src_includes/reshapers.h"

#include <iostream>
#include <vector>


int main() {

    // Run all unit tests
    if (TESTING_MODE) {
        run_arithmetic_tests();
        test_reshapers();
        run_smoother_tests();
        return 0;
    }

	return 0;
}
