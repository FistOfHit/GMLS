#pragma once
#include <vector>

template <class T>
class Matrix {
    public:
        int num_rows;
        int num_cols;
        std::vector<T> values;

        // Initialisers
        Matrix(int num_rows, int num_cols);
        Matrix(Matrix && old_matrix);
        Matrix(std::vector<T> &vector, int num_rows, int num_cols);
        virtual ~Matrix();

        T operator()(int row, int col) { return values[row*this->num_cols + col]; }
        T operator[](int index) { return values[index]; }
};

// Implementation here
template <class T>
Matrix<T>::Matrix(int num_rows, int num_cols)
    : num_rows(num_rows)
    , num_cols(num_cols) 
{
    values = std::vector<T>(num_rows*num_cols, 0);
}

template <class T>
Matrix<T>::Matrix(std::vector<T> &vector, int num_rows, int num_cols)
    : num_rows(num_rows)
    , num_cols(num_cols)
{
    values = std::move(vector);
}

template <class T>
Matrix<T>::~Matrix() {
    // Replace with a temporary empty vector, freeing memory
    std::vector<T>().swap(Matrix<T>::values);
}