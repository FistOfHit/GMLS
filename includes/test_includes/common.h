#pragma once
#include <vector>


using vector = std::vector<float>;


void test_vector_equality(const vector &a, const vector &b,
    const float tolerance = 1e-5);
void log_failure(const vector &expected, const vector &actual);