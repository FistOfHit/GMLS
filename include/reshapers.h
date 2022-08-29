#ifndef RESHAPERS_H
#define RESHAPERS_H
#endif

#include "../include/grid.h"


/* Restrict vector inv. linearly from 2^n+1 elements to 2^(n-1)+1 elements.

Notes
-----
The method implemented here (injection) simply samples alternate elements
of the vector to construct a new vector of reduced size by "injecting"
them into the new vector. Due to this multi-grid solver simulating multiple
grids by operating repeatedly on one grid, this restriction simply becomes
strided access.

The prolongation matrix (P) for this operation
looks like this:
<-   2^n+1   ->
1 0 0 0 0 ... 0    ^
0 0 1 0 0 ... 0    |
0 0 0 0 1 ... 0    |
. .           . 2^(n-1)+1
.   .         .    |
.     .       .    |
0 . . .       0    ^

As a result, this function is just a placeholder for clarity and to leave
the possibility of future methods being implemented.

Parameters
----------
Grid &vector:
    Vector to be restricted
*/
void restrict_vector(Grid &vector);


/* Interpolate vector linearly from 2^n+1 elements to 2^(n+1)+1 elements.

Notes
-----
Performs simple linear interpolation, copying elements for odd indexes but
otherwise taking a simple aritmetic average for new elements generated in
between, using the following stencil:
A simple copy (or do nothing in this case) for even indexed elements
(includes edge elements):
    [1] -> [1]
and a simple average for odd indexed elements:
    0.5 [1, 1] -> [1]

Practically, this means that every "new" element introduced by ~doubling
the size of the vector is simply the arithmetic average of its neighbours. 

Given the current depth at which this grid is at in the set of all grids
from fine->coarse, (0 -> number of grids) this function finds out which set
of values need to be interpolated into which other set using variable 
striding across the vector.

Parameters
----------
Grid &vector:
    Vector to be interpolated
*/
void interpolate_vector(Grid &vector);


/* Interpolate matrix from (2^n+1)^2 elements to (2^(n+1)+1)^2 elements.

Notes
-----
Due to this multi-grid implementation working only on one grid, an
interpolation routine isn't required. In order to interpolate a restricted
matrix, the stride used to access matrix elements is simply halved, and the
original information is still present. This method of using injection for
restriction and hence being able to simply revert to the finer grid matrix
saves a lot of memory and compute, and maintains the original information
present in the finest (original) grid, at the cost of implying that the
errors calculated after smoothing now not only come from smoothing, but
also from reshaping the solution/RHS vector.

As described in restrict_matrix, this fucntion is merely a placeholder.

Parameters
----------
Grid &vector:
    Vector to be interpolated
*/
void interpolate_matrix(Grid &matrix);


/* Restrict matrix from (2^n+1)^2 elements to (2^(n-1)+1)^2 elements.

Notes
-----
The method implemented here (injection) simply samples alternate elements
of the matrix to construct a new matrix of reduced size by "injecting"
them into the new matrix. Due to this multi-grid solver simulating multiple
grids by operating repeatedly on one grid, this restriction simply becomes
strided access.

As with vector restriction, the prolongation matrix (P) for this operation
looks like this:
<-   2^n+1   ->
1 0 0 0 0 ... 0    ^
0 0 1 0 0 ... 0    |
0 0 0 0 1 ... 0    |
. .           . 2^(n-1)+1
.   .         .    |
.     .       .    |
0 . . .       0    ^

And note that as this is matrix restriction/interpolation, the operation
reqiured is:
    PA(P^T)
Where P is the above prolongation matrix as described, and A is the LHS
matrix given in this functions parameters.

Also note that as a result, interpolation is not required, as it would just
also be strided access, with half the stride length. This function, and its 
counterpart, the matrix interpolation function, are just placeholders.

Parameters
----------
Grid &vector:
    Vector to be restricted
*/
void restrict_matrix(Grid &matrix);
