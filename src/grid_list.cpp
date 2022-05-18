#include <memory>
#include <vector>
#include "../includes/src_includes/grid_list.h"


GridList::GridList() {
    GridList::list = std::vector<std::unique_ptr<Matrix>>(0);
}


GridList::GridList(std::vector<std::unique_ptr<Matrix>> list) {
    GridList::list = std::move(list);
}


GridList::~GridList() {
    // Replace with a temporary empty vector, freeing memory
    std::vector<std::unique_ptr<Matrix>>().swap(GridList::list);
}


void GridList::sort() {

}


int GridList::size() {

}