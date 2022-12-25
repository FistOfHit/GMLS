#include "grid/grid.h"

#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <vector>


template <typename T>
Grid<T>::Grid(const size_t size, const int max_depth) :
    depth_(0),
    max_depth_(max_depth),
    num_rows_(size),
    grid_(std::vector<T>(num_rows_ * num_cols_, 0)) {}


template <typename T>
Grid<T>::Grid(
    const size_t num_rows,
    const size_t num_cols,
    const int max_depth
) :
    depth_(0),
    max_depth_(max_depth),
    num_rows_(num_rows),
    num_cols_(num_cols),
    grid_(std::vector<T>(num_rows_ * num_cols_, 0)) {}


template <typename T>
Grid<T>::Grid(const std::vector<T>&& vector, const int max_depth) :
    depth_(0),
    max_depth_(max_depth),
    num_rows_(vector.size()),
    grid_(std::move(vector)) {}
    

template <typename T>
Grid<T>::Grid(
    const std::vector<T>&& matrix,
    const size_t num_rows,
    const size_t num_cols,
    const int max_depth
) :
    depth_(0),
    max_depth_(max_depth),
    num_rows_(num_rows),
    num_cols_(num_cols),
    grid_(std::move(matrix)) {}


template <typename T>
Grid<T>::Grid(const Grid<T>& source_grid) :
    depth_(source_grid.depth()),
    max_depth_(source_grid.max_depth()),
    num_rows_(source_grid.num_rows()),
    num_cols_(source_grid.num_cols()),
    grid_(source_grid.grid()) {}


template <typename T>
Grid<T>::~Grid() {
    grid_ = std::vector<T>();
}


template <typename T>
T& Grid<T>::operator[](const size_t index) { return grid_[index]; }


template <typename T>
const T& Grid<T>::operator[](const size_t index) const { return grid_[index]; }


template <typename T>
const int Grid<T>::depth() const { return depth_; }


template <typename T>
void Grid<T>::set_depth(const int new_depth) { depth_ = new_depth; }


template <typename T>
void Grid<T>::increment_depth() { depth_++; };


template <typename T>
void Grid<T>::decrement_depth() { depth_--; };


template <typename T>
const int Grid<T>::max_depth() const { return max_depth_; }


template <typename T>
const size_t Grid<T>::num_rows() const { return num_rows_; }


template <typename T>
const size_t Grid<T>::num_cols() const { return num_cols_; }


template <typename T>
const size_t Grid<T>::size() const { return num_rows_ * num_cols_; }


template <typename T>
const int Grid<T>::stride() const { return std::pow(2, depth_); }


template <typename T>
const std::vector<T>& Grid<T>::grid() const { return grid_; }


template <typename T>
void Grid<T>::move_elements_from(const Grid<T>& target) {
    grid_ = std::move(target.grid());
}


template <typename T>
void Grid<T>::restrict() {

    if (num_rows() == 3) {
        std::cout << "Attempting to restrict from coarsest possible grid level"
            << " (vector of size 3), exiting. \n";
        return;
    }

    // Matrix case
    if (num_cols() > 1) {
        if (num_cols() == 3) {
            std::cout << "Attempting to restrict from coarsest possible grid level"
                << " (vector of size 3), exiting. \n";
            return;
        }

    // Vector case
    } else {
        // Do nothing
    }

    // Increment depth after interpolation
    increment_depth();
}


template <typename T>
void Grid<T>::interpolate() {

    if (depth() == 0) {
        std::cout << "Attempting to interpolate from finest level, exiting. \n"; 
        return;
    }

    // Matrix case
    if (num_cols() > 1) {
        // Do nothing

    // Vector case
    } else {
        // Determine half-stride length across vector for edges
        int half_stride = stride() / 2;

        // Interpolating all "new" points
        for (auto i = half_stride; i <= size() - half_stride; i += stride()) {
            (*this)[i] = 0.5 * ((*this)[i - half_stride] + (*this)[i + half_stride]);
        }
    }
    
    // Decrement depth after interpolation
    decrement_depth();
}


template <typename T>
const void Grid<T>::print(const int precision) const {

    // Storing number of digits in each element
	std::vector<int> digits_grid(size());

	// Find spaces required to print everything nicely
	size_t row_number;
	int num_digits, max_digits = 0;
	for (auto i = 0; i < num_rows(); i++) {
		row_number = i * num_cols();

		for (auto j = 0; j < num_cols(); j++) {
			num_digits = (int)std::log10((*this)[row_number + j]);
			max_digits = std::max(max_digits, num_digits);

			digits_grid[row_number + j] = num_digits;
		}
	}

	// Size of whats being printed
	std::cout << std::setprecision(precision) << std::fixed;
	std::cout << "Grid: " << num_rows() << " X " << num_cols() << "\n";
	std::cout << "[";

	// Print row by row
	int num_spaces;
	for (auto i = 0; i < num_rows(); i++) {
		row_number = i * num_cols();

		// Tidy brackets
		if (i == 0) { std::cout << "["; }
		else { std::cout << " ["; }

		// Print spaces for all but last element in each row
		for (auto j = 0; j < num_cols() - 1; j++) {
			std::cout << (*this)[row_number + j];

			// Print enough spaces to leave big enough gap
			num_spaces = max_digits - digits_grid[row_number + j] + 1;
			for (auto k = 0; k < num_spaces; k++) {
                std::cout << " ";
            }
		}

		std::cout << (*this)[row_number + num_cols() - 1];

		// Tidy brackets
		if (i == num_rows() - 1) { std::cout << "]]" << "\n"; }
		else { std::cout << "]" << "\n"; }
	}
}


template <typename T>
Grid<T>& Grid<T>::operator +=(const Grid<T>& operand) {
    for (auto i = 0; i < size(); i += stride()) {
        (*this)[i] = (*this)[i] + operand[i];
    }

    return *this;
}


template <typename T>
Grid<T>& Grid<T>::operator -=(const Grid<T>& operand){
    for (auto i = 0; i < size(); i += stride()) {
        (*this)[i] = (*this)[i] - operand[i];
    }

    return *this;
}


template <typename T>
Grid<T>& Grid<T>::operator *=(const Grid<T>& operand){

    float row_sum;
    size_t row_index;
    // Matrix-Vector multiplication (row-by-row element wise vector-vector)
    for (auto i = 0; i < num_rows(); i += stride()) {
        row_sum = 0.0F;
        row_index = i * operand.size();

        for (auto j = 0; j < num_cols(); j += stride()) {
            row_sum += (*this)[row_index + j] * operand[j];
        }

        (*this)[i] = row_sum;
    }

    return *this;
}


template <typename T>
const Grid<T> Grid<T>::operator +(const Grid<T>& operand) const {
    
    // Create a new grid as a copy of calling grid
    Grid<T> result = Grid<T>(*this);
    for (auto i = 0; i < result.size(); i += result.stride()) {
        result[i] = (*this)[i] + operand[i];
    }

    return result;
}


template <typename T>
const Grid<T> Grid<T>::operator -(const Grid<T>& operand) const {

    // Create a new grid as a copy of calling grid
    Grid<T> result = Grid<T>(*this);
    for (auto i = 0; i < result.size(); i += result.stride()) {
        result[i] = (*this)[i] - operand[i];
    }

    return result;
}


template <typename T>
const Grid<T> Grid<T>::operator *(const Grid<T>& operand) const {

    // Create a new grid with approrpiate dimensions
    Grid<T> result = Grid<T>(num_rows(), 1);
    result.set_depth(depth());

    float row_sum;
    size_t row_index;
    // Matrix-Vector multiplication (row-by-row element wise vector-vector)
    for (auto i = 0; i < num_rows(); i += stride()) {
        row_sum = 0.0F;
        row_index = i * num_cols();

        for (auto j = 0; j < num_cols(); j += stride()) {
            row_sum += (*this)[row_index + j] * operand[j];
        }

        result[i] = row_sum;
    }

    return result;
}


// Explicit instantiation
template class Grid<float>;
template class Grid<double>;
