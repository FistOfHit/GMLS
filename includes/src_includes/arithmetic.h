#include <vector>


using vector = std::vector<float>;


void add(const vector &a, const vector &b, const int grid_depth,
    vector &result);
void subtract(const vector &a, const vector &b, const int grid_depth,
    vector &result);
void multiply(const vector &a, const vector &b, const int grid_depth,
    vector &result);