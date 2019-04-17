#include <iostream>

// Custom source includes
#include "../includes/interpolation.h"
#include "../includes/IO_routines.h"
#include "../includes/grid_routines.h"
#include "../includes/restriction.h" 

// Custom test includes
#include "../includes/interpolation_tests.h"


using namespace std;


int main() {

	run_interpolation_tests();

	system("pause");

	return 0;

}