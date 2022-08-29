#define TESTING_MODE 0
#ifdef TESTING_MODE
#include "../tests/include/arithmetic_tests.h"
#include "../tests/include/cycle_tests.h"
#include "../tests/include/reshapers_tests.h"
#include "../tests/include/smoothers_tests.h"
#endif

// Source includes
#include "../include/multigrid_cycles.h"
#include "../include/printing.h"
#include "../include/reshapers.h"
#include "../include/grid.h"

#include <iostream>
#include <vector>


using vector = std::vector<float>;


// TODO: Actual loading, just a placeholder for now
vector load(std::string csv_path) {
    vector vec = vector();
    return vec;
}


// TODO: Actual writing here, just a placeholder for now
void write(vector &vec) {
    return;
}


int main() {

    // Run all unit tests
    if (TESTING_MODE) {
        run_arithmetic_tests();
        run_cycle_tests();
        run_reshapers_tests();
        run_smoother_tests();
        return 0;
    }

    Grid g = Grid(31, 3);
    std::cout << g.size() << std::endl;
    std::cout << g.max_depth() << std::endl;
    print_vector(g);

    // // Load arrays into memory (Ax=b)
    // vector a = load("./path_to_a.csv");
    // vector x = load("./path_to_x.csv");
    // vector b = load("./path_to_b.csv");

    // // Initialise residual and error vectors
    // vector residual = vector(b);
    // vector error = vector(x);

    // // Set typical hyperparameters
    // const int num_grids = 5;
    // const int num_cycles = 10;
    // const int num_iterations = 10;

    // // Run W-cycles
    // for (auto _ = 0; _ < num_cycles; _++) {
    //     w_cycle(a, x, b, residual, error, num_grids, num_iterations);
    // }

    // // Write solution to file
    // write(x);

	// return 0;
}
