#ifndef RATIONAL_HPP
#define RATIONAL_HPP 1

#include <type_traits>
#include <stdexcept>
#include "gcd.hpp"

using BaseType = int;

template <typename T>
using ValueOrConstRef = typename std::conditional<(sizeof(T) > sizeof(T*)), const T&, T>::type;



class Q
{
public:
    struct DivisionByZero : std::runtime_error
    {
        using std::runtime_error::runtime_error;
    };

    Q(BaseType init_n, BaseType init_d) : n{init_n}, d{init_d}
    {
        if (d < 0)
        {
            d = -d;
            n = -n;
        }
    }

    Q(int init_n) : Q{init_n, 1}
    {}

    Q& operator+=(const Q& rhs)
    {
        auto& lhs = *this;
        n = (rhs.d * lhs.n) + (lhs.d * rhs.n);
        d *= rhs.d;
        return *this;
    }

    Q& operator-=(const Q& rhs)
    {
        auto& lhs = *this;
        n = (rhs.d * lhs.n) - (lhs.d * rhs.n);
        d *= rhs.d;
        return *this;
    }

    Q& operator*=(const Q& rhs)
    {
        n *= rhs.n;
        d *= rhs.d;
        return *this;
    }

    Q& operator/=(const Q& rhs)
    {
        n *= rhs.d;
        d *= rhs.n;

        if (d == 0)
            throw DivisionByZero("Illegal operation: division by zero");

        if (d < 0)
        {
            d = -d;
            n = -n;
        }
        return *this;
    }

    ValueOrConstRef<BaseType> nom() const
    {
        auto gcd = euclid_GCD(n, d);
        return n / gcd;
    }

    ValueOrConstRef<BaseType> den() const
    {
        auto gcd = euclid_GCD(n, d);
        return d / gcd;
    }

private:
    void reduce()
    {
        auto gcd = euclid_GCD(n, d);
        n /= gcd;
        d /= gcd;
    }

    BaseType n;
    BaseType d;
};

inline bool operator==(const Q& lhs, const Q& rhs)
{
    return lhs.nom() * rhs.den() == rhs.nom() * lhs.den();
}

inline bool operator<(const Q& lhs, const Q& rhs)
{
    return lhs.nom() * rhs.den() < rhs.den() * lhs.nom();
}

inline bool operator>(const Q& lhs, const Q& rhs)
{
    return (not (lhs < rhs)) and (not (lhs == rhs));
}

inline bool operator!=(const Q& lhs, const Q& rhs)
{
    return not (lhs == rhs);
}

inline bool operator<=(const Q& lhs, const Q& rhs)
{
    return (lhs < rhs) or (lhs == rhs);
}

inline bool operator>=(const Q& lhs, const Q& rhs)
{
    return (lhs > rhs) or (lhs == rhs);
}

inline Q operator+(const Q& lhs, const Q& rhs)
{
    Q tmp{lhs};
    tmp += rhs;
    return tmp;
}

inline Q operator-(const Q& lhs, const Q& rhs)
{
    Q tmp{lhs};
    tmp -= rhs;
    return tmp;
}

inline Q operator*(const Q& lhs, const Q& rhs)
{
    Q tmp{lhs};
    tmp *= rhs;
    return tmp;
}

inline Q operator/(const Q& lhs, const Q& rhs)
{
    Q tmp{lhs};
    tmp /= rhs;
    return tmp;
}

inline Q inverseOf(const Q& mhs)
{
    Q tmp{1};
    tmp /= mhs;
    return tmp;
}

#endif // include guard
