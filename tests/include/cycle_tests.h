#ifndef CYCLE_TESTS_H
#define CYCLE_TESTS_H
#endif

#include <vector>


using vector = std::vector<float>;


/* Test multigrid V-cycling. */
void test_v_cycle();


/* Test multigrid W-cycling. */
void test_w_cycle();


/* Run all tests for multigrid cycle. */
void run_cycle_tests();