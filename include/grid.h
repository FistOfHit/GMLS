#pragma once

#include <cmath>
#include <cstddef>
#include <vector>


/// @brief Grid class for representing a 1 or 2D array with varying depths.
template <typename T>
class Grid {

    /// The maximum depth this grid can go down to
    int max_depth_;
    /// The number of rows in this grid (1 implies this is a 1D vector)
    size_t num_rows_ = 1;
    /// The number of columns in this grid (1 implies this is a 1D vector)
    size_t num_cols_ = 1;
    /// The grid elements data structure
    std::vector<T> grid_;

public:

    /// The current depth of all Grid instances
    static int depth;

    /// @brief Construct a 1D grid from a size and maximum depth
    ///
    /// @param size      The number of elements this grid will have
    /// @param max_depth The maximum depth this grid can go down to
    Grid(const size_t size, const int max_depth);

    /// @brief Construct a 2D grid from 2 dimensions and a maximum depth
    ///
    /// @param num_rows  The number of elements this grid will have
    /// @param num_cols  The number of columns this grid will have
    /// @param max_depth The maximum depth this grid can go down to
    Grid(const size_t num_rows, const size_t num_cols, const int max_depth);

    /// @brief Construct a 1D grid from an existing vector and a maximum depth
    ///
    /// @param vector    The vector to std::move from
    /// @param max_depth The maximum depth this grid can go down to
    Grid(const std::vector<T>&& vector, const int max_depth);

    /// @brief Construct a 2D grid from an existing vector, 2 dimensions and a maximum depth
    ///
    /// @param matrix    The vector to std::move from
    /// @param num_rows  The number of elements this grid will have
    /// @param num_cols  The number of columns this grid will have
    /// @param max_depth The maximum depth this grid can go down to
    Grid(
        const std::vector<T>&& matrix,
        const size_t num_rows,
        const size_t num_cols,
        const int max_depth
    );

    /// @brief Copy constructor
    ///
    /// @param grid Instance to copy
    Grid(const Grid<T>&);
    
    /// @brief Destructor
    ~Grid();
    
    /// @brief Add a grid, element-wise, into this one
    Grid<T>& operator +=(const Grid<T>&);

    /// @brief Subtract a grid, element-wise, from this one
    Grid<T>& operator -=(const Grid<T>&);

    /// @brief Multiply a grid, element-wise, into this one
    Grid<T>& operator *=(const Grid<T>&);

    /// @brief Add two grids and return a new one
    const Grid<T> operator +(const Grid<T>&) const;

    /// @brief Subtract two grids and return a new one
    const Grid<T> operator -(const Grid<T>&) const;

    /// @brief Multiply two grids and return a new one
    const Grid<T> operator *(const Grid<T>&) const;

    /// @brief Assign grid value at a given index
    float& operator[](const size_t index);

    /// @brief Get grid value at a given index
    const float& operator[](const size_t index) const;

    /// @brief Get maximum grid depth
    int max_depth() const;

    /// @brief Get number of rows (dimension 1)
    size_t num_rows() const;

    /// @brief Get number of columns (dimension 2)
    size_t num_cols() const;

    /// @brief Get total number of elements (dimension 1 X dimension 2)
    size_t size() const;

    /// @brief Get the stride in use to access consecutive grid elements 
    int stride() const;

    /// @brief Get the grid values
    std::vector<T> grid() const;
};
