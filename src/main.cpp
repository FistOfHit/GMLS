#define TESTING_MODE 1

#ifdef TESTING_MODE
#include "../includes/test_includes/interpolation_tests.h"
#include "../includes/test_includes/matrix_tests.h"
#include "../includes/test_includes/restriction_tests.h"
#include "../includes/test_includes/smoother_tests.h"
#endif

// Source includes
#include "../includes/src_includes/interpolation.h"
#include "../includes/src_includes/IO_routines.h"
#include "../includes/src_includes/matrix.h"
#include "../includes/src_includes/grid_routines.h"
#include "../includes/src_includes/restriction.h"

#include <iostream>
#include <vector>


int main() {

    if (TESTING_MODE) {
        // Run all unit tests
        run_interpolation_tests();
        test_matrix();
        run_restriction_tests();
        run_smoother_tests();
        return 0;
    }

    std::vector<std::vector<int>> matrix = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
    std::cout << matrix[0][2] << "\n";
	return 0;
}
