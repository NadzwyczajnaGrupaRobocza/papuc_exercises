#pragma once

#include "Range.hpp"
#include <algorithm>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <vector>
#include <boost/algorithm/cxx11/none_of.hpp>

namespace Primes
{

struct Divides
{
    Divides(unsigned dividendInit) : dividend{dividendInit}
    {
    }

    bool operator()(unsigned divisor)
    {
        return dividend % divisor == 0;
    }

private:
    unsigned dividend;
};

class PrimeRange
{
public:
    PrimeRange(unsigned Ninit) : N{Ninit}
    {
    }

    std::vector<unsigned> get()
    {
        using boost::adaptors::filtered;

        std::vector<unsigned> primes = {2};
        auto inputRange = lmlib::Range<unsigned>(3u, N + 1);

        auto indivisibleByKnownPrimes = [&](const unsigned val) {
            return boost::algorithm::none_of(primes, Divides(val));
        };

        std::copy_if(inputRange.begin(), inputRange.end(),
                     std::back_inserter(primes), indivisibleByKnownPrimes);

        // boost::copy(inputRange | filtered(indivisibleByKnownPrimes),
        //             std::back_inserter(primes));

        return primes;
    }

private:
    unsigned N;
};
}
