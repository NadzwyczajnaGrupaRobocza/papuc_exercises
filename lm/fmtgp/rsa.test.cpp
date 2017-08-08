//
//
#include <gtest/gtest.h>

#include "rsa.hpp"

TEST(lm_fmtgp_ch13, naive_prime_test_idenfies_small_primes)
{
    ASSERT_TRUE(is_prime<int>(7));
    ASSERT_TRUE(is_prime<int>(23));
    ASSERT_TRUE(is_prime<int>(101));

    ASSERT_FALSE(is_prime(561));
    ASSERT_FALSE(is_prime(4));
}

TEST(lm_fmtgp_ch13, computing_fermat_inverse)
{
    ASSERT_EQ(multiplicative_inverse_fermat(2, 5), 3);
    ASSERT_EQ(multiplicative_inverse_fermat(3, 5), 2);
    ASSERT_EQ(multiplicative_inverse_fermat(4, 5), 4);

    ASSERT_EQ(multiplicative_inverse_fermat(2, 11), 6);
    ASSERT_EQ(multiplicative_inverse_fermat(6, 11), 2);
    ASSERT_EQ(multiplicative_inverse_fermat(3, 11), 4);
    ASSERT_EQ(multiplicative_inverse_fermat(4, 11), 3);
    ASSERT_EQ(multiplicative_inverse_fermat(5, 11), 9);
    ASSERT_EQ(multiplicative_inverse_fermat(9, 11), 5);
    ASSERT_EQ(multiplicative_inverse_fermat(7, 11), 8);
    ASSERT_EQ(multiplicative_inverse_fermat(8, 11), 7);
    ASSERT_EQ(multiplicative_inverse_fermat(10, 11), 10);
}

TEST(lm_fmtgp_ch13, carmichael_test_single_application)
{
    ASSERT_TRUE(is_carmichael_number(561));
    ASSERT_TRUE(is_carmichael_number(1105));

    ASSERT_FALSE(is_carmichael_number(100));
}

TEST(lm_fmtgp_ch13, carmichael_test_create_range)
{

    const auto carmichael_numbers = first_n_carmichael_numbers(5);

    const auto expected_result = std::vector<int>{561, 1105, 1729, 2465, 2821};

    ASSERT_EQ(carmichael_numbers, expected_result);
}
