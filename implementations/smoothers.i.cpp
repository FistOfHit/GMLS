#include "../src/smoothers.cpp"


template void jacobi_smooth(
    const Grid<float>& a,
    Grid<float>& x,
    const Grid<float>& b,
    const int num_iterations,
    const float omega
);
template void jacobi_smooth(
    const Grid<double>& a,
    Grid<double>& x,
    const Grid<double>& b,
    const int num_iterations,
    const float omega
);

template void sor_smooth(
    const Grid<float>& a,
    Grid<float>& x,
    const Grid<float>& b,
    const int num_iterations,
    const float omega
);
template void sor_smooth(
    const Grid<double>& a,
    Grid<double>& x,
    const Grid<double>& b,
    const int num_iterations,
    const float omega
);
