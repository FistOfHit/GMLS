#define TESTING_MODE 1

#ifdef TESTING_MODE
#include "../includes/test_includes/interpolation_tests.h"
#include "../includes/test_includes/restriction_tests.h"
#include "../includes/test_includes/smoother_tests.h"
#endif

// Source includes
#include "../includes/src_includes/interpolation.h"
#include "../includes/src_includes/printing.h"
#include "../includes/src_includes/restriction.h"

#include <iostream>
#include <vector>


int main() {

    if (TESTING_MODE) {
        // Run all unit tests
        test_interpolation();
        test_restriction();
        test_smoothers();
        return 0;
    }

	return 0;
}
