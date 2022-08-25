#include "../include/grid.h"
#include <cstddef>
#include <vector>


using vector = std::vector<float>;


Grid::Grid(size_t size, int max_depth) :
    size_(size),
    max_depth_(max_depth),
    grid_(vector(size, 0))
{}


Grid::Grid(const Grid& source_grid) :
    size_(source_grid.size_),
    max_depth_(source_grid.max_depth_),
    grid_(source_grid.grid_)
{}


Grid::Grid(const Grid&& source_grid) :
    size_(source_grid.size_),
    max_depth_(source_grid.max_depth_),
    grid_(std::move(source_grid.grid_))
{}


size_t Grid::size() const { return size_; }


int Grid::max_depth() const { return max_depth_; }


float Grid::operator[](size_t index) { return grid_[index]; }
