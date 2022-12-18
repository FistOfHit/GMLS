#pragma once

#include "../../include/grid.h"


/// @brief Test V-cycling.
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
///                       required during the cycle
/// @param num_cycles     The number of V-cycles to perform
template <typename T>
void test_v_cycle(
    Grid<T>& a,
    Grid<T>& b,
    Grid<T>& residual,
    Grid<T>& error,
    const Grid<T> expected_values,
    const int num_iterations,
    const int num_cycles
);


/// @brief Test W-cycling.
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
///                       required during the cycle
/// @param num_cycles     The number of W-cycles to perform
template <typename T>
void test_w_cycle(
    Grid<T>& a,
    Grid<T>& b,
    Grid<T>& residual,
    Grid<T>& error,
    const Grid<T> expected_values,
    const int num_iterations,
    const int num_cycles
);
