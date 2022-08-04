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

    // Load arrays into memory (Ax=b)
    vector a = load("./path_to_a.csv");
    vector x = load("./path_to_x.csv");
    vector b = load("./path_to_b.csv");

    // Initialise residual and error vectors
    vector r = vector(b);
    vector e = vector(x);

    // Set typical hyperparameters
    const int num_grids = 5;
    const int num_cycles = 10;
    const int num_iterations = 10;

    // Run W-cycles
    for (auto _ = 0; _ < num_cycles; _++) {
        w_cycle(a, x, b, r, e, num_grids, num_iterations);
    }

    // Write solution to file
    write(x);

	return 0;
}
