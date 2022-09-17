#pragma once

#include <cmath>
#include <cstddef>
#include <vector>


/* Grid class for representing a 1 or 2D array with varying depths.

Notes
-----

Attributes
----------
private:
    static const int max_depth_ (default = 1)
        The maximum depth ALL grids can go down to when restricting 
public:
Methods
-------

*/
class Grid {
    int max_depth_;
    size_t num_rows_ = 1;
    size_t num_cols_ = 1;
    std::vector<float> grid_;

public:
    static int depth;

    Grid(const size_t size, const int max_depth);
    Grid(const size_t num_rows, const size_t num_cols, const int max_depth);
    Grid(const std::vector<float> &&vector, const int max_depth);
    Grid(const std::vector<float> &&vector, const size_t num_rows,
        const size_t num_cols, const int max_depth);
    Grid(const Grid &grid);
    Grid(Grid &&grid);
    ~Grid();

    int max_depth() const;
    size_t num_rows() const;
    size_t num_cols() const;
    size_t size() const;
    int stride() const;

    std::vector<float> grid() const;

    float &operator[](const size_t index);
    const float &operator[](const size_t index) const;

    Grid &operator=(const Grid &grid);
};
