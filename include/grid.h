#ifndef GRID_H
#define GRID_H
#endif

#include <cstddef>
#include <vector>


class Grid {
public:
    Grid(size_t size, int max_depth);
    Grid(size_t num_rows, size_t num_cols, int max_depth);
    Grid(const Grid &grid);
    Grid(Grid &&grid);
    ~Grid();

    int depth = 0;

    size_t num_rows() const;
    size_t num_cols() const;
    size_t size() const;

    int max_depth() const;
    std::vector<float> grid();

    inline float &operator[](size_t index);
    inline const float &operator[](size_t index) const;

    inline Grid &operator=(const Grid &grid);

private:
    size_t num_rows_ = 1;
    size_t num_cols_ = 1;
    int max_depth_;
    std::vector<float> grid_;
};
