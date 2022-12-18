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

    ///
    /// @brief Construct a 1D grid from a size and maximum depth
    ///
    /// @param size      The number of elements this grid will have
    /// @param max_depth The maximum depth this grid can go down to
    ///
    Grid(const size_t size, const int max_depth);

    ///
    /// @brief Construct a 2D grid from 2 dimensions and a maximum depth
    ///
    /// @param num_rows  The number of elements this grid will have
    /// @param num_cols  The number of columns this grid will have
    /// @param max_depth The maximum depth this grid can go down to
    ///
    Grid(const size_t num_rows, const size_t num_cols, const int max_depth);

    ///
    /// @brief Construct a 1D grid from an existing vector and a maximum depth
    ///
    /// @param vector    The vector to std::move from
    /// @param max_depth The maximum depth this grid can go down to
    ///
    Grid(const std::vector<T>&& vector, const int max_depth);

    ///
    /// @brief Construct a 2D grid from an existing vector, 2 dimensions and a maximum depth
    ///
    /// @param matrix    The vector to std::move from
    /// @param num_rows  The number of elements this grid will have
    /// @param num_cols  The number of columns this grid will have
    /// @param max_depth The maximum depth this grid can go down to
    ///
    Grid(
        const std::vector<T>&& matrix,
        const size_t num_rows,
        const size_t num_cols,
        const int max_depth
    );

    ///
    /// @brief Copy constructor
    ///
    /// @param grid Instance to copy
    ///
    Grid(const Grid<T>&);
    
    ~Grid();

    int max_depth() const;

    size_t num_rows() const;
    size_t num_cols() const;
    size_t size() const;
    int stride() const;
    std::vector<T> grid() const;

    /// @brief Assign grid value at a given index
    float &operator[](const size_t index);
    /// @brief Get grid value at a given index
    const float &operator[](const size_t index) const;
};
