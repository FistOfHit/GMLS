#define TESTING_MODE 1

#ifdef TESTING_MODE
#include "../includes/test_includes/interpolation_tests.h"
#include "../includes/test_includes/grid_list_tests.h"
#include "../includes/test_includes/matrix_tests.h"
#include "../includes/test_includes/restriction_tests.h"
#include "../includes/test_includes/smoother_tests.h"
#endif

// Source includes
#include "../includes/src_includes/interpolation.h"
#include "../includes/src_includes/grid_list.h"
#include "../includes/src_includes/printing.h"
#include "../includes/src_includes/matrix.h"
#include "../includes/src_includes/restriction.h"

#include <iostream>
#include <vector>


int main() {

    if (TESTING_MODE) {
        // Run all unit tests
        test_interpolation();
        test_grid_list();
        test_matrix();
        test_restriction();
        test_smoothers();
        return 0;
    }

	return 0;
}
