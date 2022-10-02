#pragma once


/* Test multigrid V-cycling. */
void test_v_cycle(Grid &a, Grid &b, Grid &residual, Grid &error,
    const Grid expected_values, const int num_iterations, const int num_cycles);


/* Test multigrid W-cycling. */
void test_w_cycle(Grid &a, Grid &b, Grid &residual, Grid& error,
    const Grid expected_values, const int num_iterations, const int num_cycles);


/* Run all tests for multigrid cycle. */
void run_cycle_tests();
