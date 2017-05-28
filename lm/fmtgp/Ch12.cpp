#include "Ch12.hpp"

#include <utility>
#include <algorithm>

int euclid_GCD(int a, int b)
{
    while (b != 0)
    {
        a = a % b;
        std::swap(a, b);
    }

    return a;
}

bool odd(int a)
{
    return static_cast<bool>(a | 0x1);
}

bool even(int a)
{
    return not odd(a);
}

int stein_GCD(int m, int n)
{
    if (n < 0) n = -n;
    if (m < 0) m = -m;
    if (m == 0) return n;
    if (n == 0) return m;

    int d_m = 0;
    while (even(m))
    {
        m >>= 1;
        ++d_m;
    }

    int d_n = 0;
    while (even(n))
    {
        m >>= 1;
        ++d_n;
    }

    while (m != n)
    {
        if (n > m) std::swap(m, n);
        m -= n;
        do m >>= 1; while (even(m));
    }

    return m << std::min(d_m, d_n);
}
