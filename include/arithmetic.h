#pragma once

#include "grid.h"


///
/// \brief Add two vectors together, element-wise into an output argument vector.
///
/// \param &a      A grid
/// \param &b      Another grid
/// \param &result (Output parameter) the result of the operation
///
template <typename T>
void add(const Grid<T>& a, const Grid<T>& b, Grid<T>& result);

///
/// \brief Subtract two vectors, element-wise into an output argument vector.
///
/// \param &a      A grid
/// \param &b      Another grid
/// \param &result (Output parameter) the result of the operation
///
template <typename T>
void subtract(const Grid<T>& a, const Grid<T>& b, Grid<T>& result);

///
/// \brief Perform a matrix vector product into an output argument vector.
///
/// \param &a      A grid
/// \param &b      Another grid
/// \param &result (Output parameter) the result of the operation
///
template <typename T>
void multiply(const Grid<T>& a, const Grid<T>& b, Grid<T>& result);
