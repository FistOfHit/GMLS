#ifndef MULTIGRID_CYCLES_H
#define MULTIGRID_CYCLES_H
#endif

#include <vector>


using vector = std::vector<float>;


/* Perform one V-cycle iteration on a series of grids.

Notes
-----
A V-cycle iteration is a single iteration of solving an Ax=b system by 
using matrix/vector restriction (downsampling, downscaling, reduction 
etc.), interpolation (upsampling, upscaling, refinement etc.) and smoothing
(gradually nudging a solution approximation towards a more accuracte
result). 

The core-concepts of multi-grid methods are that smoothing iterations are
also performed on coarser grids to:
1) reduce the total computational cost by performing smoothing on smaller
    grids
2) accelerate the elimination of low-frequency errors on the fine-grid, as
    they become high-frequency errors on coarser grids (smoothers are good
    at reducing high-frequency errors)

In particular, the "V" in V-cycle comes from the fact that the pattern in
which restriction and interpolation happen form a V-shape:

Fine-grid problem         Fine-grid soluation approximation
            \                     /
        Restriction          Interpolation
            \               /
            Lowest grid level

For more information, please refer to:
- https://en.wikipedia.org/wiki/Multigrid_method
- https://math.mit.edu/classes/18.086/2006/am63.pdf
Which are just a few of very useful sources out there on practical
implementations of multi-grid methods

Parameters
----------
std::vector<float> &a:
    LHS n x m matrix A in Ax=b
std::vector<float> &x:
    m-length solution vector x in Ax=b
std::vector<float> &b:
    n-length RHS vector b in Ax=b
std::vector<float> &residual:
    m-length residual vector for storing the values of b - Ax', where x' is
    some intermediate/approximation of x
std::vector<float> &error:
    m-length error vector e for solving Ae=residual, and storing the error
    values to correct x with
const int num_grids:
    The number of grids to be used in this multigrid cycle
const int num_iterations (default = 3):
    The number of iterations to apply smoothers whenever required during
    the cycle */
void v_cycle(vector &a, vector &x, vector &b, vector &residual, vector &error,
    const int num_grids, const int num_iterations);


/* Perform one W-cycle iteration on a series of grids.

Notes
-----
A W-cycle iteration is a single iteration of solving an Ax=b system by 
using matrix/vector restriction (downsampling, downscaling, reduction 
etc.), interpolation (upsampling, upscaling, refinement etc.) and smoothing
(gradually nudging a solution approximation towards a more accuracte
result). 

The core-concepts of multi-grid methods are that smoothing iterations are
also performed on coarser grids to:
1) reduce the total computational cost by performing smoothing on smaller
    grids
2) accelerate the elimination of low-frequency errors on the fine-grid, as
    they become high-frequency errors on coarser grids (smoothers are good
    at reducing high-frequency errors)

In particular, the "W" in W-cycle comes from the fact that the pattern in
which restriction and interpolation happen form a W-shape:

Fine-grid problem                          Fine-grid solution approximation
        \                                            /
        Restriction    Intermediate grid level    Interpolation
            \            /              \            /
            Lowest grid level          Lowest grid level

In practice, there are many more grid levels used when applying
multi-grid methods, and the exact shape of the intermediate cycles forming
the W will change.

For more information, please refer to:
- https://en.wikipedia.org/wiki/Multigrid_method
- https://math.mit.edu/classes/18.086/2006/am63.pdf
Which are just a few of very useful sources out there on practical
implementations of multi-grid methods

Parameters
----------
std::vector<float> &a:
    LHS n x m matrix A in Ax=b
std::vector<float> &x:
    m-length Solution vector x in Ax=b
std::vector<float> &b:
    n-length RHS vector b in Ax=b
std::vector<float> &r:
    m-length residual vector for storing the values of b - Ax', where x' is
    some intermediate/approximation of x
std::vector<float> &e:
    m-length error vector e for solving Ae=residual, and storing the error
    values to correct x with
const int num_grids:
    The number of grids to be used in this multigrid cycle
const int num_iterations (default = 3):
    The number of iterations to apply smoothers whenever required during
    the cycle */
void w_cycle(vector &a, vector &x, vector &b, vector &residual, vector &error,
    const int num_grids, const int num_iterations);