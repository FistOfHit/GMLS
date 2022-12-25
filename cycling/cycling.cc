#include "cycling/cycling.h"
#include "grid/grid.h"
#include "smoothers/smoothers.h"

#include <iostream>


template <typename T>
void restrict(
    Grid<T>& a,
    Grid<T>& x,
    Grid<T>& b,
    Grid<T>& residual,
    Grid<T>& error,
    const int num_iterations,
    const int final_depth
) {
    // Presmooth x at initial depth
    sor_smooth(a, x, b, num_iterations);

    // Find the current residual
    residual = b - (a * x);

    // Restrict residual (and LHS matrix)
    a.restrict();
    x.restrict();
    b.restrict();
    residual.restrict();
    error.restrict();

    // Restrict down to coarsest grid
    for (auto _ = x.depth(); _ < final_depth; _++) {
        // Presmooth x at finer level
        sor_smooth(a, error, residual, num_iterations);

        // Find the current residual
        residual -= (a * error);

        // Restrict
        a.restrict();
        x.restrict();
        b.restrict();
        residual.restrict();
        error.restrict();
    }

    // Further smooth on coarsest grid
    sor_smooth(a, error, residual, num_iterations);
}


template <typename T>
void interpolate(
    Grid<T>& a,
    Grid<T>& x,
    Grid<T>& b,
    Grid<T>& residual,
    Grid<T>& error,
    const int num_iterations,
    const int final_depth
) {
    // Interpolate up to second-finest mesh
    for (auto _ = x.depth(); _ > final_depth + 1; _--) {
        // Map the correction from the coarse grid to a finer grid
        a.interpolate();
        x.interpolate();
        b.interpolate();
        error.interpolate();
        residual.interpolate();

        // Apply a post-smoother to Ax=b
        sor_smooth(a, error, residual, num_iterations);
    }

    // Map the correction from the second finest grid to the finest grid
    a.interpolate();
    x.interpolate();
    b.interpolate();
    error.interpolate();
    residual.interpolate();

    // Apply a post-smoother to Ax=b
    x += error;
    sor_smooth(a, x, b, num_iterations);
}


template <typename T>
void v_cycle(
    Grid<T>& a,
    Grid<T>& x,
    Grid<T>& b,
    Grid<T>& residual,
    Grid<T>& error,
    const int num_iterations,
    const int final_depth
) {
    // Restrict and smooth all the way down to coarsest grid depth
    restrict(a, x, b, residual, error, num_iterations, x.max_depth());

    // Interpolate and smooth all the way up to final grid depth
    interpolate(a, x, b, residual, error, num_iterations, final_depth);
}


template <typename T>
void w_cycle(
    Grid<T>& a,
    Grid<T>& x,
    Grid<T>& b,
    Grid<T>& residual,
    Grid<T>& error,
    const int num_iterations
) {
    // V-cycle repeatedly at varying depths to form the W-cycle.
    // __builtin_ctz used to generate depths for the W-cycle pattern.
    for (auto i = 2; i < std::pow(2, x.max_depth() + 1); i += 2) {
        v_cycle(a, x, b, residual, error, num_iterations,
            x.max_depth() - __builtin_ctz(i));
    }
    
    // Restrict everything once and interpolate back to top to end V-cycles
    a.restrict();
    x.restrict();
    b.restrict();
    error.restrict();
    residual.restrict();

    interpolate(a, x, b, residual, error, num_iterations, 0);
}


// Explicit instantiation
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
