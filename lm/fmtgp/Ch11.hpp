#ifndef PAPUC_LM_FMTGP_CH11
#define PAPUC_LM_FMTGP_CH11 1

#include <utility>
#include <iterator>

#include <iterator_concepts.hpp>
#include "Ch04.hpp"

namespace fmtgp
{

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

template <typename It>
It rotate(It f, It m, It l, std::forward_iterator_tag)
{
    if (f == m) return l;
    if (m == l) return f;

    auto p = swap_ranges(f, m, m, l);
    while (p.first != m or p.second != l)
    {
        if (p.second == l)
        {
            rotate_unguarded(p.first, m, l);
            return p.first;
        }
        f = m;
        m = p.second;
        p = swap_ranges(f, m, m, l);
    }

    return m;
}

template <typename It>
using ValueType = typename std::iterator_traits<It>::value_type;

template <typename It>
using DifferenceType = typename std::iterator_traits<It>::difference_type;

template <typename It, typename F>
void rotate_cycle_from(It i, F from)
{
    ValueType<It> tmp = *i;
    It start = i;
    for (It j = from(i); j != start; j = from(j))
    {
        *i = *j;
        i = j;
    }
    *i = tmp;
}

template <RandomAccessIterator It>
struct rotate_transform
{
    DifferenceType<It> plus;
    DifferenceType<It> minus;
    It m1;

    rotate_transform(It f, It m, It l)
        : plus{m - f}, minus{m - l}, m1{f + (l - m)}
    {}

    It operator()(It i) const
    {
        return i + ((i < m1)? plus : minus);
    }
};

template <RandomAccessIterator It>
It rotate(It f, It m, It l, std::random_access_iterator_tag)
{
    if (f == m) return l;
    if (m == l) return f;
    DifferenceType<It> cycles = gcd(m - f, l - m);
    rotate_transform<It> rotator(f, m, l);
    while (cycles-- > 0)
    {
        rotate_cycle_from(f + cycles, rotator);
    }
    return rotator.m1;
}

template <BidirectionalIterator It>
std::pair<It, It> reverse_until(It f, It m, It l)
{
    while (f != m and m != l) std::swap(*f++, *--l);
    return {f, l};
}

template <BidirectionalIterator It>
It rotate(It f, It m, It l, std::bidirectional_iterator_tag)
{
    reverse(f, m);
    reverse(m, l);
    auto p = reverse_until(f, m, l);
    reverse(p.first, p.second);
    if (m == p.first)
    {
        return p.second;
    }
    else
    {
        return p.first;
    }
}

template <Iterator It>
It rotate(It f, It m, It l)
{
    return rotate(f, m, l, typename std::iterator_traits<It>::iterator_category{});
}

template <BidirectionalIterator It>
void reverse(It f, It l, std::bidirectional_iterator_tag)
{
    while (f != l and f != --l)
    {
        std::swap(*f++, *l);
    }
}

template <Iterator It>
void reverse(It f, It l)
{
    reverse(f, l, typename std::iterator_traits<It>::iterator_category{});
}

}

#endif // PAPUC_LM_FMTGP_CH11
