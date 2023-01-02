#include "common_tests.h"
#include "grid.h"

#include <include/gtest/gtest.h>
#include <include/gmock/gmock.h>


void test_grid_equality(const Grid<double>& a, const Grid<double>& b) {

    auto tol = 1e-4;

    // Check size (not dimensions) for compatibility first
    ASSERT_EQ(a.size(), b.size()) << "Size mismatch";

    EXPECT_THAT(
        a.grid(), 
        testing::Pointwise(
            testing::FloatNear(tol),
            b.grid()
        )
    ) << "Value mismatch";
}
