#include "../src/multigrid_cycle_tests.cpp"


template void test_v_cycle(
    Grid<float>& a,
    Grid<float>& b,
    Grid<float>& residual,
    Grid<float>& error,
    const Grid<float> expected_values,
    const int num_iterations,
    const int num_cycles
);

template void test_w_cycle(
    Grid<float>& a,
    Grid<float>& b,
    Grid<float>& residual,
    Grid<float>& error,
    const Grid<float> expected_values,
    const int num_iterations,
    const int num_cycles
);
