#include "grid/grid.h"

#include <vector>

int main() {
   
    auto x = Grid<double>(std::vector<double>{1.33, 2.14324, 1231}, 1);
    x.print();
    return 0;
}
