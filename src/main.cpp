#define TESTING_MODE 1
#ifdef TESTING_MODE

// Test includes
#include "../tests/include/arithmetic_tests.h"
#include "../tests/include/multigrid_cycle_tests.h"
#include "../tests/include/reshapers_tests.h"
#include "../tests/include/smoothers_tests.h"
#endif

// Source includes
#include "../include/grid.h"
#include "../include/multigrid_cycles.h"
#include "../include/printing.h"
#include "../include/reshapers.h"

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

    Grid<float> g = Grid<float>(31, 3);
    std::cout << g.size() << std::endl;
    std::cout << g.max_depth() << std::endl;
    print_grid(g);
}
