#pragma once
#include <cmath>
#include <limits>
#include <type_traits>

namespace fp
{
template <typename _Fp>
bool equal(_Fp a, _Fp b)
{
    static_assert(std::is_floating_point<_Fp>::value,
                  "fp::equal can only be used with floating point types");
    return std::fabs(a - b) < std::numeric_limits<_Fp>::epsilon();
}

template <typename _Fp>
bool not_equal(_Fp a, _Fp b)
{
    static_assert(std::is_floating_point<_Fp>::value,
                  "fp::not_equal can only be used with floating point types");
    return std::fabs(a - b) >= std::numeric_limits<_Fp>::epsilon();
}
}
