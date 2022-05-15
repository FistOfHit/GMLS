#include <vector>
#include "../includes/src_includes/matrix.h"


Matrix::Matrix(int num_rows, int num_cols, int initial_value) {
    Matrix::num_rows = num_rows;
    Matrix::num_cols = num_cols;
    
    std::vector<int> values(num_rows*num_cols, initial_value);
    Matrix::values = values;
}


Matrix::Matrix(const std::vector<int> vector, int num_rows, int num_cols) {
    Matrix::num_rows = num_rows;
    Matrix::num_cols = num_cols;
    Matrix::values = vector;
}


Matrix::~Matrix() {
    // Replace with a temporary empty vector, freeing memory
    std::vector<int>().swap(Matrix::values);
}

