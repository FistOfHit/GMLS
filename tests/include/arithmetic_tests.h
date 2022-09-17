#pragma once

#include "../../include/grid.h"


/* Test Grid addition. */
void test_add(const Grid &a, const Grid &b, const Grid &expected_values);


/* Test Grid subtraction. */
void test_subtract(const Grid &a, const Grid &b, const Grid &expected_values);


/* Test matrix-Grid multiplication. */
void test_multiply(const Grid &matrix, const Grid &vector,
    const Grid &expected_values);


/* Run all tests for arithmetic operators. */
void run_arithmetic_tests();
