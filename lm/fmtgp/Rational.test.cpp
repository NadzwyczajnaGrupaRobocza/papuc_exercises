#include <gtest/gtest.h>
#include "Rational.hpp"

TEST(lm_fmtgp_rational, willReduceUponConstruction)
{
    auto p = Q{11, 121};

    ASSERT_EQ(p.nom(), 1);
    ASSERT_EQ(p.den(), 11);
}

TEST(lm_fmtgp_rational, willMoveSignToNominator)
{
    auto p = Q{2, -4};

    ASSERT_EQ(p.nom(), -1);
    ASSERT_EQ(p.den(), 2);
}

TEST(lm_fmtgp_rational, willImplementEqualityOperator)
{
    auto p = Q{1, 2};
    auto q = Q{2, 4};
    auto r = Q{4, 7};

    ASSERT_TRUE(p == q);
    ASSERT_FALSE(p == r);
}

TEST(lm_fmtgp_rational, willImplementOperatorPlusEquals)
{
    auto p = Q{1, 3};
    const auto q = Q{1, 6};
    auto expected_result = Q{1, 2};

    p += q;
    ASSERT_EQ(p, expected_result);
}

TEST(lm_fmtgp_rational, willAllowChainingOnOperatorPlusEquals)
{
    auto p = Q{1, 3};
    const auto q = Q{1, 6};
    const auto r = Q{1, 2};

    (p += q) += r;

    ASSERT_EQ(p, 1);
}
