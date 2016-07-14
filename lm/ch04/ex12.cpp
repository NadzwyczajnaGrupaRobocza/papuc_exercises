#include "Primes.hpp"
#include "gtest/gtest.h"

TEST(LMCh04Ex12, willFindFirstTenPrimes)
{
    auto primes = Primes::PrimeRange(10).get();
    auto expected = std::vector<unsigned>{2u, 3u, 5u, 7u};
    ASSERT_EQ(expected, primes);
}

TEST(LMCh04Ex12, willFindFirstHundredPrimes)
{
    auto primes = Primes::PrimeRange(100u).get();
    auto expected = std::vector<unsigned>{2,  3,  5,  7,  11, 13, 17, 19, 23,
                                          29, 31, 37, 41, 43, 47, 53, 59, 61,
                                          67, 71, 73, 79, 83, 89, 97};
    ASSERT_EQ(expected, primes);
}
