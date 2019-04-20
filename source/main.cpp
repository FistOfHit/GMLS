#include <iostream>

// Custom source includes
#include "../includes/interpolation.h"
#include "../includes/IO_routines.h"
#include "../includes/grid_routines.h"
#include "../includes/restriction.h" 

// Custom test includes
#include "../includes/interpolation_tests.h"
#include "../includes/restriction_tests.h"
#include "../includes/smoother_tests.h"


using namespace std;


int main() {

	// Running some tests
	run_interpolation_tests();
	run_restriction_tests();
	run_smoother_tests();

	system("pause");

	return 0;

}