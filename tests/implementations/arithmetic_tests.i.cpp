#include "../src/arithmetic_tests.cpp"

template void test_add(
    const Grid<float>& a,
    const Grid<float>& b,
    const Grid<float>& expected_values
);

template void test_subtract(
    const Grid<float>& a,
    const Grid<float>& b,
    const Grid<float>& expected_values
);

template void test_multiply(
    const Grid<float>& test_matrix,
    const Grid<float>& test_grid,
    const Grid<float>& expected_values
);
