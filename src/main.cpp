#include <iostream>

// Source includes
#include "../includes/src_includes/interpolation.h"
#include "../includes/src_includes/IO_routines.h"
#include "../includes/src_includes/grid_routines.h"
#include "../includes/src_includes/restriction.h"

// Test includes
#include "../includes/test_includes/interpolation_tests.h"
#include "../includes/test_includes/restriction_tests.h"
#include "../includes/test_includes/smoother_tests.h"


using namespace std;


int main() {

	// Running some tests
	run_interpolation_tests();
	run_restriction_tests();
	run_smoother_tests();

	system("pause");

	return 0;

}
