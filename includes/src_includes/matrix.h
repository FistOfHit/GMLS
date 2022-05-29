#pragma once
#include <vector>


class Matrix {
    public:
        int num_rows;
        int num_cols;
        std::vector<double> values;

        // Initialisers
        Matrix(double initial_value, int num_rows, int num_cols);
        Matrix(std::vector<double> vector, int num_rows, int num_cols);
        virtual ~Matrix();

        inline double operator()(int row, int col) { return values[row*this->num_cols + col]; }
};
