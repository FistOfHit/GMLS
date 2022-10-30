#include "../include/grid.h"

#include <cmath>
#include <cstddef>
#include <vector>


template <typename Numerical>
using vector = std::vector<Numerical>;


Grid::Grid(const size_t size, const int max_depth) :
    max_depth_(max_depth),
    num_rows_(size),
    grid_(vector(num_rows_ * num_cols_, 0)) {
    depth = 0;
}


Grid::Grid(const size_t num_rows, const size_t num_cols, const int max_depth) :
    max_depth_(max_depth),
    num_rows_(num_rows),
    num_cols_(num_cols),
    grid_(vector(num_rows_ * num_cols_, 0)) {
    depth = 0;
}


Grid::Grid(const vector&& vector, const int max_depth) :
    max_depth_(max_depth),
    num_rows_(vector.size()),
    grid_(std::move(vector)) {
    depth = 0;
}
    
    
Grid::Grid(const vector&& matrix, const size_t num_rows,
    const size_t num_cols, const int max_depth) :
    max_depth_(max_depth),
    num_rows_(num_rows),
    num_cols_(num_cols),
    grid_(std::move(matrix)) {
    depth = 0;
}


Grid::Grid(const Grid& source_grid) :
    max_depth_(source_grid.max_depth()),
    num_rows_(source_grid.num_rows()),
    num_cols_(source_grid.num_cols()),
    grid_(source_grid.grid()) {
    depth = source_grid.depth;
}


Grid::Grid(Grid&& source_grid) :
    max_depth_(source_grid.max_depth()),
    num_rows_(source_grid.num_rows()),
    num_cols_(source_grid.num_cols()),
    grid_(std::move(source_grid.grid())) {
    depth = source_grid.depth;

    source_grid.num_rows_ = 0;
    source_grid.num_cols_ = 0;
    source_grid.grid_ = vector();
}


Grid::~Grid() {
    grid_ = vector();
}


int Grid::depth;


int Grid::max_depth() const { return max_depth_; }


size_t Grid::num_rows() const { return num_rows_; }


size_t Grid::num_cols() const { return num_cols_; }


size_t Grid::size() const { return num_rows_ * num_cols_; }


int Grid::stride() const { return std::pow(2, depth); }


vector Grid::grid() const { return grid_; }


float &Grid::operator[](const size_t index) { return grid_[index]; }


const float &Grid::operator[](const size_t index) const { return grid_[index]; }


Grid &Grid::operator=(const Grid &source_grid) {

    depth = source_grid.depth;

    max_depth_ = source_grid.max_depth_;
    num_rows_ = source_grid.num_rows_;
    num_cols_ = source_grid.num_cols_;
    grid_ = std::move(source_grid.grid_);

    return *this;
}
