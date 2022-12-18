#include "../src/reshapers.cpp"


template void interpolate_vector(Grid<float>& vector);
template void restrict_vector(Grid<float>& vector);
template void interpolate_matrix(Grid<float>& matrix);
template void restrict_matrix(Grid<float>& matrix);
