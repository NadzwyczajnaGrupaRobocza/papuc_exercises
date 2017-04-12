#pragma once

#include <utility>

template <typename Iter0, typename Iter1>
std::pair<Iter0, Iter1> swap_ranges(Iter0 first0, Iter0 last0, Iter1 first1,
                                    Iter1 last1)
{
    while (first0 != last0 and first1 != last1)
    {
        std::swap(*first0++, *first1++);
    }

    return {first0, first1};
}

template <typename It>
void gries_mills_rotate(It f, It m, It l)
{
    // u = distance(f, m) ; v = distance(m, l)
    if (f == m or m == l)
        return; // u == 0 or v == 0

    auto p = swap_ranges(f, m, m, l);

    while (p.first != m or p.second != l)
    {
        if (p.first == m) // u < v
        {
            f = m;
            m = p.second; // v <- v - u
        }
        else // v < u
        {
            f = p.first; // u <- u - v
        }
        p = swap_ranges(f, m, m, l);
    }
    return; // u == v
}

template <typename It>
void rotate_unguarded(It f, It m, It l)
{
    // assert(f != m and m != l)
    auto p = swap_ranges(f, m, m, l);
    while (p.first != m or p.second != l)
    {
        f = p.first;
        if (m == f) m = p.second;
        p = swap_ranges(f, m, m, l);
    }
}
