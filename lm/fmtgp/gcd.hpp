#ifndef GCD_HPP
#define GCD_HPP

#include <algorithm>

int stein_GCD(int m, int n);
int euclid_GCD(int a, int b);

namespace gcd
{
template <typename T>
T remainder(T a, T b)
{
    return a % b;
}

// template <>
// int remainder(int a, int b)
// {
//     return a % b;
// }

template <typename T>
T half(T x)
{
    return x / 2;
}

// template <>
// int half(int x)
// {
//     return x / 2;
// }

template <typename T>
T largest_doubling(T a, T b)
{
    while (a - b >= b)
    {
        b = b + b;
    }

    return b;
}

template <typename T>
std::pair<T, T> quotient_remainder(T a, T b)
{
    if (a < b)
    {
        return {T{0}, a};
    }

    T c = largest_doubling(a, b);
    a = a - c;
    T n{1};
    while (c != b)
    {
        c = half(c);
        n = n + n;
        if (c <= a)
        {
            a = a - c;
            n = n + 1;
        }
    }
    return {n, a};
}

template <typename E>
E gcd(E a, E b)
{
    while (b != E{0})
    {
        a = remainder(a, b);
        std::swap(a, b);
    }
    return a;
}

template <typename E>
std::pair<E, E> extended_gcd(E a, E b)
{
    E x0{1};
    E x1{0};
    while (b != E{0})
    {
        auto qr = quotient_remainder(a, b);
        E x2 = x0 - qr.first * x1;
        x0 = x1;
        x1 = x2;
        a = b;
        b = qr.second;
    }

    return {x0, a};
}
}

#endif // include guard
