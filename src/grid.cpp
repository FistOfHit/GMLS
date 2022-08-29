#include "../include/grid.h"

#include <cstddef>
#include <vector>


Grid::Grid(size_t size, int max_depth) :
    num_rows_(size),
    max_depth_(max_depth),
    grid_(std::vector<float>(num_rows_ * num_cols_, 0))
{}


Grid::Grid(size_t num_rows, size_t num_cols, int max_depth) :
    num_rows_(num_rows),
    num_cols_(num_cols),
    max_depth_(max_depth),
    grid_(std::vector<float>(num_rows_ * num_cols_, 0))
{}


Grid::Grid(const Grid& source_grid) :
    num_rows_(source_grid.num_rows_),
    num_cols_(source_grid.num_cols_),
    max_depth_(source_grid.max_depth_),
    grid_(source_grid.grid_)
{}


Grid::Grid(Grid&& source_grid) :
    num_rows_(source_grid.num_rows_),
    num_cols_(source_grid.num_cols_),
    max_depth_(source_grid.max_depth_),
    grid_(std::move(source_grid.grid_))
{}


Grid::~Grid() {
    grid_ = std::vector<float>();
}


size_t Grid::num_rows() const { return num_rows_; }


size_t Grid::num_cols() const { return num_cols_; }


size_t Grid::size() const { return num_rows_ * num_cols_; }


int Grid::max_depth() const { return max_depth_; }


std::vector<float> Grid::grid() { return grid_; }


float &Grid::operator[](size_t index) { return grid_[index]; }


const float &Grid::operator[](size_t index) const { return grid_[index]; }


// Grid &Grid::operator=(const Grid &source_grid) {

//     max_depth_ = source_grid.max_depth_;
//     num_rows_ = source_grid.num_rows_;
//     num_cols_ = source_grid.num_cols_;
//     grid_ = std::move(source_grid.grid_);

//     return *this;
// }
