#include "../src/multigrid_cycles.cpp"


template void restrict(
    Grid<float>& a,
    Grid<float>& x,
    Grid<float>& b,
    Grid<float>& residual,
    Grid<float>& error,
    const int num_iterations,
    const int final_depth
);
template void restrict(
    Grid<double>& a,
    Grid<double>& x,
    Grid<double>& b,
    Grid<double>& residual,
    Grid<double>& error,
    const int num_iterations,
    const int final_depth
);

template void interpolate(
    Grid<float>& a,
    Grid<float>& x,
    Grid<float>& b,
    Grid<float>& residual,
    Grid<float>& error,
    const int num_iterations,
    const int final_depth
);
template void interpolate(
    Grid<double>& a,
    Grid<double>& x,
    Grid<double>& b,
    Grid<double>& residual,
    Grid<double>& error,
    const int num_iterations,
    const int final_depth
);

template void v_cycle(
    Grid<float>& a,
    Grid<float>& x,
    Grid<float>& b,
    Grid<float>& residual,
    Grid<float>& error,
    const int num_iterations,
    const int final_depth
);
template void v_cycle(
    Grid<double>& a,
    Grid<double>& x,
    Grid<double>& b,
    Grid<double>& residual,
    Grid<double>& error,
    const int num_iterations,
    const int final_depth
);

template void w_cycle(
    Grid<float>& a,
    Grid<float>& x,
    Grid<float>& b,
    Grid<float>& residual,
    Grid<float>& error,
    const int num_iterations
);
template void w_cycle(
    Grid<double>& a,
    Grid<double>& x,
    Grid<double>& b,
    Grid<double>& residual,
    Grid<double>& error,
    const int num_iterations
);
