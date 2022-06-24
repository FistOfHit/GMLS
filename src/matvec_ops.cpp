#include <vector>


std::vector<float>* add(const std::vector<float> a, const std::vector<float> b, std::vector<float> result) {
    /* Add two vectors together, element-wise.

    */
    
    for (auto i = 0; i < a.size(); i++) {
        result[i] = a[i] + b[i];
    }
}


std::vector<float>* subtract(const std::vector<float> a, const std::vector<float> b, std::vector<float> result) {
    /*
    */

    for (auto i = 0; i < a.size(); i++) {
        result[i] = a[i] - b[i];
    }
}


std::vector<float>* multiply(const std::vector<float> a, const std::vector<float> b, std::vector<float> result) {

    const size_t num_rows = b.size();
    const size_t num_cols = a.size()/b.size();

    float row_sum;
    size_t row_num;
    for (auto i = 0; i < num_rows; i++) {
        row_sum = 0;
        row_num = i * num_cols;
        
        for (auto j = 0; j < num_rows; j++) {
            row_sum += a[row_num + j] * b[j];
        }

        result[i] = row_sum;
    }
}