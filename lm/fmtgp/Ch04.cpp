#include "Ch04.hpp"
#include "fp_manip.hpp"

std::pair<integer, line_segment> quotient_remainder(line_segment a, line_segment b)
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
