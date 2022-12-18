#include "../src/reshapers_tests.cpp"


template void test_grid_interpolation(
    const Grid<float>& coarse,
    const Grid<float>& expected_values
);

template void test_grid_restriction(
    const Grid<float>& fine,
    const Grid<float>& expected_values
);
