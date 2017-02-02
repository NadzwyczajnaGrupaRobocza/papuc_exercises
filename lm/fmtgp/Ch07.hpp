#pragma once

bool odd(int n);
int half(int n);


// clang-format off

template <typename G>
concept bool NonCommutativeAdditiveSemigroup = requires(G x)
{
    { x + x }-> G;
};

template <typename T>
concept bool Integer = requires(T x)
{
    { x + x } -> T;
    { x == x } -> bool
    { odd(x) } -> bool;
    { half(x) } -> bool;
};
// clang-format on

template <NonCommutativeAdditiveSemigroup A, typename N>
A multiply_accumulate(A r, N n, A a)
{
    while (true)
    {
        if (odd(n))
        {
            r = r + a;
            if (n == 1)
            {
                return r;
            }
        }
        n = half(n);
        a = a + a;
    }
}

template <NonCommutativeAdditiveSemigroup A, Integer N>
A multiply_accumulate_semigroup(A r, N n, A a)
{
    // precondition n >= 0
    if (n == 0)
        return r;
    while (true)
    {
        if (odd(n))
        {
            r += a;
            if (n == 1)
                return r;
        }
        n = half(n);
        a += a;
    }
}
