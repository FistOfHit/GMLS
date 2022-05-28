#include <iostream>
#include <memory>
#include "../includes/src_includes/grid_list.h"
#include "../includes/test_includes/grid_list_tests.h"


void test_base_constructor() {
    std::cout << "Grid-List base-constructor test: ";

    GridList test_list = GridList();
    if (test_list.list.size() != 0) {
        std::cout << "FAIL" << "\n";
        std::cout << "Expected Grid-List size: 0" << "\n";
		std::cout << "Actual Grid-list size:  " << test_list.list.size() << "\n";
        return;
    }

    std::cout << "PASS" << "\n";
}


void test_vector_constructor() {
    std::cout << "Grid-List vector-constructor test: ";

    // Create a Matrix first then duplicate into a grid list
    // std::vector<int> test_vector(5*5, 0);
    // std::unique_ptr<Matrix> test_matrix = std::make_unique<Matrix>(test_vector, 5, 5);
    // std::vector<std:unique_ptr<Matrix>> test_grids = std::vector<std::unique_ptr<Matrix>>(test_matrix, 3);
}


void test_grid_list() {
	test_base_constructor();
    test_vector_constructor();
}
