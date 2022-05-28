#pragma once
#include <memory>
#include <vector>
#include "matrix.h"


class GridList {
    public:
        std::vector<std::unique_ptr<Matrix>> list;

        GridList();
        GridList(std::vector<std::unique_ptr<Matrix>> list);
        virtual ~GridList();

        inline int size() { return GridList::list.size(); }

        inline std::unique_ptr<Matrix>& operator[](int index) { return list[index]; }
};