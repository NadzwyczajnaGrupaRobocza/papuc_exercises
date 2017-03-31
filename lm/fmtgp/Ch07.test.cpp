#include "Ch07.hpp"
#include <gtest/gtest.h>

TEST(lm_fmtgp_ch07, will_run_multiply_accumulate)
{
    ASSERT_EQ(multiply_accumulate(0u, 7, 2u), 14u);
}

TEST(lm_fmtgp_ch07, will_run_multiply_accumulate_semigroup)
{
    ASSERT_EQ(multiply_accumulate_semigroup(10u, 5, 2u), 20u);
}
