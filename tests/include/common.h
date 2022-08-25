#ifndef COMMON_H
#define COMMON_H
#endif

#include <vector>


using vector = std::vector<float>;


/* Test if two vectors are equal to within a given tolerance. */
void test_vector_equality(const vector &a, const vector &b,
    const float tolerance = 0.00001F);


/* Log a mismatch failure to stdout. */
void log_failure(const vector &expected, const vector &actual);