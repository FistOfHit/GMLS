#include "../include/grid.h"

#include <cstddef>
#include <vector>


template <typename T>
Grid<T>::Grid(const size_t size, const int max_depth) :
    max_depth_(max_depth),
    num_rows_(size),
    grid_(std::vector<T>(num_rows_ * num_cols_, 0)) {
    depth = 0;
}


template <typename T>
Grid<T>::Grid(
    const size_t num_rows,
    const size_t num_cols,
    const int max_depth
) :
    max_depth_(max_depth),
    num_rows_(num_rows),
    num_cols_(num_cols),
    grid_(std::vector<T>(num_rows_ * num_cols_, 0)) {
    depth = 0;
}


template <typename T>
Grid<T>::Grid(const std::vector<T>&& vector, const int max_depth) :
    max_depth_(max_depth),
    num_rows_(vector.size()),
    grid_(std::move(vector)) {
    depth = 0;
}
    

template <typename T>
Grid<T>::Grid(
    const std::vector<T>&& matrix,
    const size_t num_rows,
    const size_t num_cols,
    const int max_depth
) :
    max_depth_(max_depth),
    num_rows_(num_rows),
    num_cols_(num_cols),
    grid_(std::move(matrix)) {
    depth = 0;
}


template <typename T>
Grid<T>::Grid(const Grid<T>& source_grid) :
    max_depth_(source_grid.max_depth()),
    num_rows_(source_grid.num_rows()),
    num_cols_(source_grid.num_cols()),
    grid_(source_grid.grid()) {
    depth = source_grid.depth;
}


template <typename T>
Grid<T>::~Grid() {
    grid_ = std::vector<T>();
}


template <typename T>
Grid<T>& Grid<T>::operator +=(const Grid<T>& operand) {
    for (auto i = 0; i < this->size(); i += this->stride()) {
        (*this)[i] = (*this)[i] + operand[i];
    }

    return *this;
}


template <typename T>
Grid<T>& Grid<T>::operator -=(const Grid<T>& operand){
    for (auto i = 0; i < this->size(); i += this->stride()) {
        (*this)[i] = (*this)[i] - operand[i];
    }

    return *this;
}


template <typename T>
Grid<T>& Grid<T>::operator *=(const Grid<T>& operand){

    float row_sum;
    size_t row_index;
    // Matrix-Vector multiplication (row-by-row element wise vector-vector)
    for (auto i = 0; i < this->num_rows(); i += this->stride()) {
        row_sum = 0.0F;
        row_index = i * operand.size();

        for (auto j = 0; j < this->num_cols(); j += this->stride()) {
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
    Grid<T> result = Grid<T>(this->num_rows(), 1);
    result.depth = this->depth;

    float row_sum;
    size_t row_index;
    // Matrix-Vector multiplication (row-by-row element wise vector-vector)
    for (auto i = 0; i < this->num_rows(); i += this->stride()) {
        row_sum = 0.0F;
        row_index = i * this->num_cols();

        for (auto j = 0; j < this->num_cols(); j += this->stride()) {
            row_sum += (*this)[row_index + j] * operand[j];
        }

        result[i] = row_sum;
    }

    return result;
}


template <typename T>
float& Grid<T>::operator[](const size_t index) { return grid_[index]; }


template <typename T>
const float& Grid<T>::operator[](const size_t index) const { return grid_[index]; }


template <typename T>
int Grid<T>::depth;


template <typename T>
int Grid<T>::max_depth() const { return max_depth_; }


template <typename T>
size_t Grid<T>::num_rows() const { return num_rows_; }


template <typename T>
size_t Grid<T>::num_cols() const { return num_cols_; }


template <typename T>
size_t Grid<T>::size() const { return num_rows_ * num_cols_; }


template <typename T>
int Grid<T>::stride() const { return std::pow(2, depth); }


template <typename T>
std::vector<T> Grid<T>::grid() const { return grid_; }
