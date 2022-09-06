#pragma once

#include <cmath>
#include <cstddef>
#include <vector>


class Grid {
    int max_depth_ = 1;
    size_t num_rows_ = 1;
    size_t num_cols_ = 1;
    std::vector<float> grid_;

public:
    static int depth;

    Grid(const size_t size, const int max_depth);
    Grid(const size_t num_rows, const size_t num_cols, const int max_depth);
    Grid(const Grid &grid);
    Grid(Grid &&grid);
    ~Grid();

    int max_depth() const;
    size_t num_rows() const;
    size_t num_cols() const;
    size_t size() const;
    int stride() const;

    std::vector<float> grid();

    inline float &operator[](const size_t index);
    inline const float &operator[](const size_t index) const;

    inline Grid &operator=(const Grid &grid);
};
