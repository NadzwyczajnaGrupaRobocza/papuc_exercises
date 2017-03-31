#include "Ch04.hpp"
#include "fp_manip.hpp"

namespace fmtgp
{

template <typename T>
void next_fib(std::pair<T,T>& fib)
{
    fib = std::make_pair(fib.second, fib.second + fib.first);
}

template<typename T>
void last_fib(std::pair<T,T>& fib)
{
    fib = std::make_pair(fib.second - fib.first, fib.first);
}

integer quotient_fibonacci(line_segment a, line_segment b)
{
    // Precondition: b > 0
    if (a < b)
    {
        return integer{0};
    }

    auto fib_dvsr = std::make_pair(b, b);
    auto fib_base = std::make_pair(1, 1);

    do
    {
        next_fib(fib_dvsr);
        next_fib(fib_base);
    } while (a >= fib_dvsr.second);

    integer n{0};
    do
    {
        if (a >= fib_dvsr.first)
        {
            a = a - fib_dvsr.first;
            n += fib_base.first;
        }

        last_fib(fib_dvsr);
        last_fib(fib_base);

    } while (fib_dvsr.first < fib_dvsr.second);

    return n;
}

line_segment remainder_fibonacci(line_segment a, line_segment b)
{
    // Precondition: b > 0
    if (a < b)
    {
        return a;
    }

    line_segment c = b;
    do
    {
        line_segment tmp = c;
        c = b + c;
        b = tmp;
    } while (a >= c);

    do
    {
        if (a >= b)
        {
            a = a - b;
        }
        line_segment tmp = c - b;
        c = b;
        b = tmp;
    } while (b < c);

    return a;
}

std::pair<integer, line_segment> quotient_remainder(line_segment a,
                                                    line_segment b)
{
    // Precondition: b > 0
    if (a < b)
    {
        return {integer{0}, a};
    }

    line_segment c = largest_doubling(a, b);
    integer n{1};
    a = a - c;
    while (fp::not_equal(c, b))
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

integer quotient(line_segment a, line_segment b)
{
    // Precondition: b > 0
    if (a < b)
    {
        return integer{0};
    }

    line_segment c = largest_doubling(a, b);

    integer n{1};
    a = a - c;
    while (fp::not_equal(c, b))
    {
        c = half(c);
        n = n + n;
        if (c <= a)
        {
            a = a - c;
            n = n + 1;
        }
    }
    return n;
}

line_segment remainder(line_segment a, line_segment b)
{
    // Precondition: b != 0
    if (a < b)
        return a;

    line_segment c = largest_doubling(a, b);
    a = a - c;
    while (fp::not_equal(c, b))
    {
        c = half(c);
        if (c <= a)
            a = a - c;
    }

    return a;
}

line_segment largest_doubling(line_segment a, line_segment b)
{
    // precondition: b != 0
    while (a - b >= b)
    {
        b = b + b;
    }
    return b;
}

line_segment half(line_segment a)
{
    return a / 2;
}


line_segment gcm_remainder(line_segment a, line_segment b)
{
    while (fp::not_equal(b, 0.0))
    {
        a = remainder(a, b);
        std::swap(a, b);
    }

    return a;
}

integer gcd(integer a, integer b)
{
    while (b != integer{0})
    {
        a = a % b;
        std::swap(a, b);
    }

    return a;
}

}
