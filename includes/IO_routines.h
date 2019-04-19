#pragma once
#include <string>


using namespace std;


void read_matrix(double* matrix, int num_rows, int num_cols, string filename);
void write_matrix(double* matrix, int num_rows, int num_cols, string filename);

void read_vector(double* vector, int size, string filename);
void write_vector(double* vector, int size, string filename);

void print_matrix(double* matrix, int num_rows, int num_cols);
void print_vector(double* vector, int size);