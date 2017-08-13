#ifndef LM_FMTGP_RSA_HPP
#define LM_FMTGP_RSA_HPP 1

#include <vector>
#include <limits>
#include <type_traits>
#include <random>
#include "gcd.hpp"

template <typename T>
using value_or_cref = typename std::conditional<(sizeof(T) > sizeof(T*)), const T&, T>::type;

#if defined(__cpp_concepts)
// clang-format off
template <typename T>
concept bool Integer = requires(T x)
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
#else
#define Integer typename
#endif

template <Integer I>
bool odd(I n)
{
    return n % I{2} == 1;
}

template <Integer I>
bool even(I n)
{
    return n % I{2} == 0;
}

template <Integer I>
I half(I n)
{
    return n / I{2};
}

template <Integer I>
bool divides(value_or_cref<I> i, value_or_cref<I> n)
{
    return n % i == I{0};
}

template <Integer I>
I smallest_divisor(I n)
{
    if (even<I>(n))
        return I{2};
    for (auto i{3}; i * i <= n; i += I{2})
    {
        if (divides<I>(i, n))
            return i;
    }
    return n;
}

template <Integer I>
I is_prime(const I& n)
{
    return n > I{1} && (smallest_divisor(n) == n);
}

template <Integer I>
struct modulo_multiply
{
    I modulus;
    modulo_multiply(const I& i) : modulus{i}
    {}

    I operator() (const I& n, const I& m) const
    {
        return (m * n) % modulus;
    }
};

template <Integer I>
I identity_element(const modulo_multiply<I>&)
{
    return I{1};
}

template <Integer I>
I multiplicative_inverse_fermat(I a, I p)
{
    return power_monoid(a, p - 2, modulo_multiply<I>(p));
}

template <typename A, Integer N, typename MonoidOp>
A power_monoid(A a, N n, MonoidOp op)
{
    if (n == 0)
        return identity_element(op);
    return power_semigroup(a, n, op);
}

template <typename A, Integer N, typename SemigroupOp>
A power_semigroup(A a, N n, SemigroupOp op)
{
    while (not odd(n))
    {
        a = op(a, a);
        n = half(n);
    }

    if (n == 1) return a;
    return power_accumulate_semigroup(a, op(a, a), half(n - 1), op);
}

template <typename A, Integer N, typename SemigroupOp>
A power_accumulate_semigroup(A r, A a, N n, SemigroupOp op)
{
    if (n == 0)
        return r;
    while (true)
    {
        if (odd(n))
        {
            r = op(r, a);
            if (n == 1) return r;
        }

        n = half(n);
        a = op(a, a);
    }
}

template <Integer I>
I fermat_remainder(I n, I a)
{
    return power_semigroup(a, n - I{1}, modulo_multiply<I>(n));
}

template <Integer I>
bool fermat_test(I n, I witness)
{
    return fermat_remainder(n, witness) == I{1};
}

template <Integer I>
bool coprime(I a, I b)
{
    return gcd::gcd(a, b) == I{1};
}

template <Integer I>
std::vector<std::pair<I, I>> carmichael_test_vector(I n)
{
    std::vector<std::pair<I, I>> tv;

    if (is_prime(n))
        return tv;

    for (I b = I{3}; b < n; b += I{2})
    {
        if (coprime(b, n))
        {
            tv.push_back(std::make_pair(b, fermat_remainder(n, b)));
        }
    }

    return tv;
}

template <Integer I>
bool is_carmichael_number(I n)
{
    if (is_prime(n))
        return false;

    for (I b = I{3}; b < n; b += I{2})
    {
        if (coprime(b, n) and not fermat_test(n, b))
        {
            return false;
        }
    }

    return true;
}

template <Integer I>
std::vector<I> first_n_carmichael_numbers(I n)
{
    std::vector<I> result;
    result.reserve(n);
    I candidate{1};
    while (result.size() < static_cast<std::size_t>(n))
    {
        candidate += I{2};
        if (is_carmichael_number(candidate))
        {
            result.push_back(candidate);
        }

        if (candidate == std::numeric_limits<I>::max())
            break;
    }

    return result;
}

template <Integer I>
bool miller_rabin_test(I n, I q, I k, I w)
{
    modulo_multiply<I> mmult(n);
    I x = power_semigroup(w, q, mmult);
    if (x == I{1} or x == n - I{1})
        return true;

    for (I i{1}; i < k; ++i)
    {
        x = mmult(x, x);
        if (x == n - I{1})
            return true;
        if (x == I{1})
            return false;
    }
    return false;
}

template <typename I>
I random_value_from_range(I begin, I end)
{
    static std::default_random_engine e{std::random_device{}()};

    std::uniform_int_distribution<I> uniform_distr(begin, end);

    return uniform_distr(e);
}

template <Integer I>
bool is_prime_mrt(I n)
{
    if ((even(n) and n > I{2}) or n < I{2})
        return false;

    if (n == I{2})
        return true;


    I k{0};
    I q{n - 1};

    while (even(q))
    {
        k++;
        q /= 2;
    }

    I w{random_value_from_range(I{1}, n - I{1})};

    return miller_rabin_test(n, q, k, w);
}



#endif // include guard
