#ifndef GRID_H
#define GRID_H
#endif

#include <cstddef>
#include <vector>


using vector = std::vector<float>;


class Grid {
public:
    Grid(size_t size, int max_depth);
    Grid(const Grid& grid);
    Grid(const Grid&& grid);
    ~Grid();

    size_t size() const;
    int max_depth() const;
    vector grid() const;

    float operator[](size_t index);
    float operator()(size_t index);

private:
    size_t size_;
    int max_depth_;
    vector grid_;
};