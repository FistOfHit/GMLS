#pragma once
#include <string>


void read_matrix();
void write_matrix(double* matrix, int num_rows, int num_cols, std::string filename);

void read_vector(double* vector, int size, std::string filename);
void write_vector(double* vector, int size, std::string filename);

void print_matrix(double* matrix, int num_rows, int num_cols, int precision = 3);
void print_vector(double* vector, int size, int precision = 3);
