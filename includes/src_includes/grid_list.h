#pragma once
#include <memory>
#include <vector>
#include "matrix.h"


class GridList {
    public:
        std::vector<Matrix> list;

        GridList();
        GridList(std::vector<Matrix> list);
        virtual ~GridList();

        inline int size() { return GridList::list.size(); }

        inline Matrix& operator[](int index) { return list[index]; }
};