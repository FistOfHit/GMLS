#pragma once
#include <vector>


using vector = std::vector<float>;


void test_vector_equality(const vector &a, const vector &b,
    const float tolerance = 0.00001F);
void log_failure(const vector &expected, const vector &actual);