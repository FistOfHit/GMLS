#pragma once

#include "grid.h"


/* Perform a given number of Jacobi smoothing iterations on Ax=b.

Notes
-----
Performs weighted Jacobi smoothing on a solution vector for a system 
defined by Ax=b. The weighting factor Omega controls the proportion of the
update that consists of the calculated solution and the previous value.
The Jacobi algorithm does not require the latest solutions from the current
timestep as they are calculated, and so at the cost of making a copy of the
"old" solution or previous timestep, the update step can be paralellised to
any degree.

Parameters
----------
const Grid &a:
    The LHS matrix A in Ax=b
Grid &x:
    The solution vector x in Ax=b
const Grid &b:
    The RHS vector b in Ax=b
const int grid_depth:
    The depth at which this grid is in the fine->coarse stages of grids
const int num_iterations:
    The number of iterations to apply the smoother for
const int omega (default: 0.6F):
    The weighting factor Omega */
void jacobi_smooth(const Grid &a, Grid &x, const Grid &b,
    const int num_iterations, const float omega = 0.6F);


/* Perform a given number of SOR smoothing iterations on Ax=b.

Notes
-----
Performs weighted Sucessive Over-Relaxation (SOR) smoothing on a solution
vector for a system defined by Ax=b. The weighting factor Omega controls
the proportion of the update that consists of the calculated solution and
the previous value. The SOR algorithm requires the latest solutions from
the current timestep as they are calculated, and so the algorithm cannot
be trivially paralellised. This implementation does not apply any
paralellisation.

Parameters
----------
const Grid &a:
    The LHS matrix A in Ax=b
Grid &x:
    The solution vector x in Ax=b
const Grid &b:
    The RHS vector b in Ax=b
const int grid_depth:
    The depth at which this grid is in the fine->coarse stages of grids
const int num_iterations:
    The number of iterations to apply the smoother for
const int omega (default: 1.0F):
    The weighting factor Omega
*/
void sor_smooth(const Grid &a, Grid &x, const Grid &b, const int num_iterations,
    const float omega = 1.0F);
