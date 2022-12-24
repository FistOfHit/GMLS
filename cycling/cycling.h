#pragma once

#include "grid/grid.h"


/// @brief Perform restriction (first half of a V-cycle) on a series of grids.
///
/// Performs restriction, with smoothing, from the initial given grid level 
/// down to the final grid level. This is the first half of a V-cycle. For more
/// information, please refer to the notes in the docstrings for `v_cycle()`. 
/// 
/// @param a              LHS n x m matrix A in Ax=b
/// @param x              m-length solution vector x in Ax=b
/// @param b              n-length RHS vector b in Ax=b
/// @param residual       m-length residual vector for storing the values of 
///                       b - Ax', where x' is some intermediate/approximation 
///                       of x
/// @param error          m-length error vector e for solving Ae=residual, and
///                       storing the error values to correct x with
/// @param num_iterations The number of iterations to apply smoothers whenever
///                       required during the cycle (default: 3)
/// @param final_depth    The grid depth at which this process ends at
template <typename T>
void restrict(
    Grid<T>& a,
    Grid<T>& x,
    Grid<T>& b,
    Grid<T>& residual,
    Grid<T>& error,
    const int num_iterations,
    const int final_depth
);


/// @brief Perform interpolation (second half of a V-cycle) on a series of 
///        grids.
///
///
/// Performs interpolation, with smoothing, from the initial grid level up to the
/// final grid level. This is the second half of a V-cycle. For more information,
/// please refer to the notes in the docstrings for `v_cycle()`. 
///
/// @param a              LHS n x m matrix A in Ax=b
/// @param x              m-length solution vector x in Ax=b
/// @param b              n-length RHS vector b in Ax=b
/// @param residual       m-length residual vector for storing the values of 
///                       b - Ax', where x' is some intermediate/approximation 
///                       of x
/// @param error          m-length error vector e for solving Ae=residual, and
///                       storing the error values to correct x with
/// @param num_iterations The number of iterations to apply smoothers whenever
///                       required during the cycle (default: 3)
/// @param final_depth    The grid depth at which this process ends at
template <typename T>
void interpolate(
    Grid<T>& a,
    Grid<T>& x,
    Grid<T>& b,
    Grid<T>& residual,
    Grid<T>& error,
    const int num_iterations,
    const int final_depth
);


/// @brief Perform one V-cycle iteration on a series of grids.
///
/// A V-cycle iteration is a single iteration of solving an Ax=b system by 
/// using matrix/vector restriction (downsampling, downscaling, reduction 
/// etc.), interpolation (upsampling, upscaling, refinement etc.) and smoothing
/// (gradually nudging a solution approximation towards a more accuracte
/// result). 
///
/// The core-concepts of multi-grid methods are that smoothing iterations are
/// also performed on coarser grids to:
/// 1) reduce the total computational cost by performing smoothing on smaller
///     grids
/// 2) accelerate the elimination of low-frequency errors on the fine-grid, as
///     they become high-frequency errors on coarser grids (smoothers are good
///     at reducing high-frequency errors)
///
/// In particular, the "V" in V-cycle comes from the fact that the pattern in
/// which restriction and interpolation happen form a V-shape:
///
/// Fine-grid problem         Fine-grid soluation approximation
///             \                     /
///         Restriction          Interpolation
///             \               /
///             Lowest grid level
///
/// For more information, please refer to:
/// - https://en.wikipedia.org/wiki/Multigrid_method
/// - https://math.mit.edu/classes/18.086/2006/am63.pdf
/// Which are just a few of very useful sources out there on practical
/// implementations of multi-grid methods
///
/// @param a              LHS n x m matrix A in Ax=b
/// @param x              m-length solution vector x in Ax=b
/// @param b              n-length RHS vector b in Ax=b
/// @param residual       m-length residual vector for storing the values of 
///                       b - Ax', where x' is some intermediate/approximation 
///                       of x
/// @param error          m-length error vector e for solving Ae=residual, and
///                       storing the error values to correct x with
/// @param num_iterations The number of iterations to apply smoothers whenever
///                       required during the cycle (default: 3)
/// @param final_depth    The grid depth at which this process ends at
template <typename T>
void v_cycle(
    Grid<T>& a,
    Grid<T>& x,
    Grid<T>& b,
    Grid<T>& residual,
    Grid<T>& error,
    const int num_iterations,
    const int final_depth
);


/// @brief Perform one W-cycle iteration on a series of grids.
///
/// @details W-cycle iteration is a single iteration of solving an Ax=b system
/// by using matrix/vector restriction (downsampling, downscaling, reduction 
/// etc.), interpolation (upsampling, upscaling, refinement etc.) and smoothing
/// (gradually nudging a solution approximation towards a more accuracte
/// result). 
///
/// The core-concepts of multi-grid methods are that smoothing iterations are
/// also performed on coarser grids to:
/// 1) reduce the total computational cost by performing smoothing on smaller
///     grids
/// 2) accelerate the elimination of low-frequency errors on the fine-grid, as
///     they become high-frequency errors on coarser grids (smoothers are good
///     at reducing high-frequency errors)
///
/// In particular, the "W" in W-cycle comes from the fact that the pattern in
/// which restriction and interpolation happen form a W-shape:
///
/// Fine-grid problem                          Fine-grid solution approximation
///         \                                            /
///         Restriction    Intermediate grid level    Interpolation
///            \            /              \            /
///             Lowest grid level          Lowest grid level
///
/// In practice, there are many more grid levels used when applying
/// multi-grid methods, and the exact shape of the intermediate cycles forming
/// the W will change.
///
/// For more information, please refer to:
/// - https://en.wikipedia.org/wiki/Multigrid_method
/// - https://math.mit.edu/classes/18.086/2006/am63.pdf
/// Which are just a few of very useful sources out there on practical
/// implementations of multi-grid methods
///
///
/// @param a              LHS n x m matrix A in Ax=b
/// @param x              m-length solution vector x in Ax=b
/// @param b              n-length RHS vector b in Ax=b
/// @param residual       m-length residual vector for storing the values of 
///                       b - Ax', where x' is some intermediate/approximation 
///                       of x
/// @param error          m-length error vector e for solving Ae=residual, and
///                       storing the error values to correct x with
/// @param num_iterations The number of iterations to apply smoothers whenever
///                       required during the cycle (default: 3)
template <typename T>
void w_cycle(
    Grid<T>& a,
    Grid<T>& x,
    Grid<T>& b,
    Grid<T>& residual,
    Grid<T>& error,
    const int num_iterations
);
