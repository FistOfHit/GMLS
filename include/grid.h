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

    /// @brief Construct a 1D grid from a size and max depth
    ///
    /// @param size      The number of elements this grid will have
    /// @param max_depth The maximum depth this grid can go down to
    Grid(const size_t size, const int max_depth);

    /// @brief Construct a 2D grid from 2 sizes and a max depth
    ///
    /// @param num_rows  The number of elements this grid will have
    /// @param num_cols  The number of columns this grid will have
    /// @param max_depth The maximum depth this grid can go down to
    Grid(const size_t num_rows, const size_t num_cols, const int max_depth);

    /// @brief Construct a 1D grid from an existing vector and a max depth
    ///
    /// @param vector    The vector to std::move from
    /// @param max_depth The maximum depth this grid can go down to
    Grid(const std::vector<T>&& vector, const int max_depth);

    /// @brief Construct a 2D grid from an existing vector, 2 sizes, and a max depth
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

    /// @brief Restrict grid from 2^n+1 elements to 2^(n-1)+1 elements
    ///
    /// @details The method implemented here (injection) simply samples 
    /// alternate elements of the vector to construct a new vector of reduced
    /// size by "injecting" them into the new vector. Due to this multi-grid
    /// solver simulating multiple grids by operating repeatedly on one grid,
    /// this restriction simply becomes strided access.
    ///
    /// As a result, this function is just a placeholder for clarity and to
    /// leave the possibility of future methods being implemented.
    ///
    /// The prolongation matrix (P) for this operation
    /// looks like this:
    ///     <-   2^n+1   ->
    ///     1 0 0 0 0 ... 0    ^
    ///     0 0 1 0 0 ... 0    |
    ///     0 0 0 0 1 ... 0    |
    ///     . .           . 2^(n-1)+1
    ///     .   .         .    |
    ///     .     .       .    |
    ///     0 . . .       0    ^
    ///
    /// Note that if this grid has more than 1 column (2D vector, matrix) the 
    /// operation reqiured is:
    ///     PA(P^T)
    ///
    void restrict();

    /// @brief Interpolate vector from 2^n+1 elements to 2^(n+1)+1 elements.
    ///
    /// @details Performs simple linear interpolation, copying elements for odd
    /// indexes but otherwise taking a simple aritmetic average for new
    /// elements generated in between, using the following stencil:
    /// A simple copy (or do nothing in this case) for even indexed elements
    /// (includes edge elements):
    ///     [1] -> [1]
    /// and a simple average for odd indexed elements:
    ///     0.5 [1, 1] -> [1]
    ///
    /// Practically, this means that every "new" element introduced by
    /// ~doubling the size of the vector is simply the arithmetic average of
    /// its neighbours. 
    ///
    /// Given the current depth at which this grid is at in the set of all
    /// grids from fine->coarse, (0 -> number of grids) this function finds out
    /// which set of values need to be interpolated into which other set using
    /// variable striding across the vector.
    ///
    /// Due to this multi-grid implementation working only on one grid, a
    /// matrix interpolation routine isn't required. In order to interpolate a
    /// restricted matrix, the stride used to access matrix elements is simply
    /// halved, and the original information is still present. This method of
    /// using injection for restriction and hence being able to simply revert
    /// to the finer grid matrix saves a lot of memory and compute, and
    /// maintains the original information present in the finest (original)
    /// grid, at the cost of implying that the errors calculated after
    /// smoothing now not only come from smoothing, but also from reshaping the
    /// solution/RHS vector.
    void interpolate();
    
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
