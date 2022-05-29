#include <vector>
#include "../includes/src_includes/matrix.h"


Matrix::Matrix(double initial_value, int num_rows, int num_cols) {
    Matrix::num_rows = num_rows;
    Matrix::num_cols = num_cols;
    
    std::vector<double> values(num_rows*num_cols, initial_value);
    Matrix::values = values;
}


Matrix::Matrix(const std::vector<double> vector, int num_rows, int num_cols) {
    Matrix::num_rows = num_rows;
    Matrix::num_cols = num_cols;
    Matrix::values = vector;
}


Matrix::~Matrix() {
    // Replace with a temporary empty vector, freeing memory
    std::vector<double>().swap(Matrix::values);
}

