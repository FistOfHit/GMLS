#pragma once

/*
Headers
*/
#include <cmath>
#include <cstddef>
#include <vector>


template <typename Numerical>
using vector = std::vector<Numerical>;


/* 
\brief Grid class for representing a 1 or 2D array with varying depths.

Notes
-----

public:
    static int depth
        

Methods
-------
    Grid(const size_t size, const int max_depth)
        A 1D grid constructor when a grid size and max depth are provided
    Grid(const size_t num_rows, const size_t num_cols, const int max_depth)
        A 2D grid constructor when two dimenstions and max depth are provided
    Grid(const vector &&vector, const int max_depth)
        A 1D grid constructor when a vector and a max depth are provided
    Grid(const vector &&matrix, const size_t num_rows,
        const size_t num_cols, const int max_depth)
        A 2D grid constructor when a vector, 2 dimensions and a max depth
        are provided
    Grid(const Grid &grid);
        A grid copy constructor
    Grid(Grid &&grid);
        A grid move constructor
    

*/
class Grid {

    /// The maximum depth this grid can go down to
    int max_depth_;
    /// The number of rows in this grid (1 implies this is a 1D vector)
    size_t num_rows_ = 1;
    /// The number of columns in this grid (1 implies this is a 1D vector)
    size_t num_cols_ = 1;
    /// The grid elements data structure
    vector grid_;

public:
    /// The current depth of all Grid instances
    static int depth;

    ///
    /// \brief Construct a 1D grid from a size and maximum depth
    ///
    /// \param size      The number of elements this grid will have
    /// \param max_depth The maximum depth this grid can go down to
    ///
    Grid(const size_t size, const int max_depth);

    ///
    /// \brief Construct a 2D grid from 2 dimensions and a maximum depth
    ///
    /// \param num_rows  The number of elements this grid will have
    /// \param num_cols  The number of columns this grid will have
    /// \param max_depth The maximum depth this grid can go down to
    ///
    Grid(const size_t num_rows, const size_t num_cols, const int max_depth);

    ///
    /// \brief Construct a 1D grid from an existing vector and a maximum depth
    ///
    /// \param vector    The vector to std::move from
    /// \param max_depth The maximum depth this grid can go down to
    ///
    Grid(const vector&& vector, const int max_depth);

    ///
    /// \brief Construct a 2D grid from an existing vector, 2 dimensions and a maximum depth
    ///
    /// \param matrix    The vector to std::move from
    /// \param num_rows  The number of elements this grid will have
    /// \param num_cols  The number of columns this grid will have
    /// \param max_depth The maximum depth this grid can go down to
    ///
    Grid(const vector&& matrix, const size_t num_rows, const size_t num_cols, const int max_depth);

    ///
    /// \brief Copy constructor
    ///
    /// \param grid Instance to copy
    ///
    Grid(const Grid& grid);

    ///
    /// \brief Move constructor
    ///
    Grid(Grid&&) noexcept;

    ///
    /// /brief Move assignement
    ///
    Grid& operator=(Grid&&);
    
    ///
    /// \brief Destructor
    ///
    ~Grid();

    /*
    \brief Get the maximum depth of this Grid
    */
    int max_depth() const;

    /*
    \brief Get the number of rows 
    */
    size_t num_rows() const;
    size_t num_cols() const;
    size_t size() const;
    int stride() const;

    vector grid() const;

    float &operator[](const size_t index);
    const float &operator[](const size_t index) const;

};
