#include "Median.hpp"
#include "gtest/gtest.h"
#include <vector>

TEST(LMCh04Ex02, willHandleSmallInput)
{
    auto median = lm::Median<double>({1.0, 3.0, 5.0, 7.1, 9.2});
    ASSERT_DOUBLE_EQ(5.0, median.get());
}
