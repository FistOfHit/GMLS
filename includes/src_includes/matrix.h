#pragma once
#include <vector>


class Matrix {
    public:
        int num_rows;
        int num_cols;
        std::vector<int> values;

        // Initialisers
        Matrix(int num_rows, int num_cols, int initial_value);
        Matrix(const std::vector<int> vector, int num_rows, int num_cols);
        virtual ~Matrix();
};
