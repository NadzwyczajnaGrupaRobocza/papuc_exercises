#pragma once
#include <utility>

namespace fmtgp
{

using integer = int;
using line_segment = double;

integer quotient_fibonacci(line_segment a, line_segment b);
line_segment remainder_fibonacci(line_segment, line_segment);
std::pair<integer, line_segment> quotient_remainder(line_segment, line_segment);
integer quotient(line_segment, line_segment);
line_segment remainder(line_segment, line_segment);
line_segment largest_doubling(line_segment, line_segment);
line_segment half(line_segment);

line_segment gcm_remainder(line_segment, line_segment);

// clang-format off
template <typename T>
concept bool IntegralType = requires(T x)
{
    { x + x } -> T;
    { x - x } -> T;
    { x * x } -> T;
    { x / x } -> T
    { x % x } -> T;
    { x == x } -> bool;
    { x < x } -> bool;
    { x > x } -> bool;
    { x <= x } -> bool;
    { x >= x } -> bool;

};
// clang-format on
template <IntegralType T>
T gcd(T a, T b)
{
    while (b != T{0})
    {
        a = a % b;
        std::swap(a, b);
    }

    return a;
}
}
