#include "../src/common.cpp"


template void test_grid_equality(
    const Grid<float>& expected,
    const Grid<float>& actual,
    const float tolerance
);

template void log_failure(
    const Grid<float> &expected, 
    const Grid<float> &actual
);
