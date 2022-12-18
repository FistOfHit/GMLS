#include "../src/smoothers_tests.cpp"


template void test_smoothers(
    const Grid<float>& test_matrix,
    const Grid<float>& test_grid,
    const Grid<float>& expected_values,
    const int num_iterations
);
