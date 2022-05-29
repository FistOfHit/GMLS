#include <vector>
#include "../includes/src_includes/grid_list.h"


GridList::GridList() {
    GridList::list = std::vector<Matrix>(0);
}


GridList::GridList(std::vector<Matrix> list) {
    GridList::list = std::move(list);
}


GridList::~GridList() {
    // Replace with a temporary empty vector, freeing memory
    std::vector<Matrix>().swap(GridList::list);
}
