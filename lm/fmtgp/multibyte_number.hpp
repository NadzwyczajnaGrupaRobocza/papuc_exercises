#ifndef MULTIBYTE_NUMBER_HPP
#define MULTIBYTE_NUMBER_HPP

#include <iostream>

#include <bitset>
#include <algorithm>
#include <array>
#include <cstdint>
#include <iomanip>
#include <iterator>
#include <tuple>

struct endianness
{
    static constexpr bool big_endian()
    {
        union {
            std::uint16_t i;
            std::uint8_t c[2];
        } probe = {0x0102};

        return probe.c[0] == 1;
    }
};

template<int N>
class multibyte_number
{
public:
    using Byte = std::uint8_t;
    static constexpr int BITS_PER_UNIT = (__CHAR_BIT__ * sizeof(Byte));
private:
    static constexpr std::size_t WORDS_NEEDED_FOR_NUMBER_OF_BITS(std::size_t n)
    {
        return (n / BITS_PER_UNIT + ((n % BITS_PER_UNIT == 0) ? 0 : 1 ));
    }

    using Data = std::array<Byte, N>;
    using TwoBytes = std::uint16_t;

    union Converter
    {
        TwoBytes result;
        Byte byte[2];
    };

public:
    multibyte_number(std::uint32_t n)
    {
        static_assert(N >= 4, "");

        union
        {
            std::uint32_t v;
            Byte conv[4];
        } c{};
        c.v = n;

        if (endianness::big_endian())
        {
            for (int i = 0; i < 4; ++i)
            {
                value_[i] = c.conv[3 - i];
            }
        }
        else
        {
            for (int i = 0; i < 4; ++i)
            {
                value_[i] = c.conv[i];
            }
        }
    }

    multibyte_number(std::array<Byte, N> init)
        : value_{}
    {
        std::copy(init.rbegin(), init.rend(), value_.begin());
    }

    multibyte_number()
        : value_{}
    {
        std::fill(value_.begin(), value_.end(), Byte{});
    }

    const auto& value() const
    {
        return value_;
    }

    std::string str() const
    {
        std::stringstream out;
        auto f{out.flags()};
        out << "0x" << std::hex << std::setw(2) << std::setfill('0');
        for (int i = static_cast<int>(value().size() - 1);
             i >= 0;
             --i)
        {
            out << std::setw(2) << static_cast<int>(value()[i]);
        }

        out.flags(f);
        return out.str();
    }

    bool equal_to(const multibyte_number& rhs) const
    {
        return value_ == rhs.value_;
    }

    multibyte_number& operator+=(const multibyte_number& rhs)
    {
        Byte carry = 0;
        for (int i = 0; i < N; ++i)
        {
            std::tie(value_[i], carry) = add_with_carry(value_[i], rhs.value_[i], carry);
        }

        return *this;
    }

    multibyte_number<N>& operator<<=(const int shift)
    {
        if (shift <= 0)
            return *this;

        const int byte_shift = shift / BITS_PER_UNIT;
        const int bit_shift  = shift % BITS_PER_UNIT;

        if (bit_shift == 0)
        {
            for (auto n = N - 1; n >= byte_shift; --n)
            {
                value_[n] = value_[n - byte_shift];
            }
        }
        else
        {
            const auto compliment_bit_shift = (BITS_PER_UNIT - bit_shift);
            for (auto n = N - 1; n > byte_shift; --n)
            {
                value_[n] = static_cast<typename Data::value_type>(
                    (value_[n - byte_shift] << bit_shift)
                    | (value_[n - byte_shift - 1] >> compliment_bit_shift));
            }
            value_[byte_shift] = static_cast<typename Data::value_type>(value_[0] << bit_shift);
        }

        std::fill(value_.begin(), value_.begin() + byte_shift, static_cast<Byte>(0));
        return *this;
    }

    multibyte_number<N>& operator>>=(const int shift)
    {
        if (shift <= 0)
            return *this;

        const auto byte_shift = shift / BITS_PER_UNIT;
        const auto bit_shift  = shift % BITS_PER_UNIT;
        const auto limit      = N - byte_shift - 1;

        if (bit_shift == 0)
        {
            for (auto n = 0; n <= limit; ++n)
            {
                value_[n] = value_[n + byte_shift];
            }
        }
        else
        {
            const auto compliment_bit_shift = (BITS_PER_UNIT - bit_shift);
            for (auto n = 0; n < limit; ++n)
            {
                value_[n] = static_cast<typename Data::value_type>(
                    (value_[n + byte_shift] >> bit_shift)
                    | (value_[n + byte_shift + 1] << compliment_bit_shift));
            }
            value_[limit] = static_cast<typename Data::value_type>(value_[N - 1] >> bit_shift);
        }
        std::fill(value_.begin() + limit + 1, value_.end(), static_cast<Byte>(0));

        return *this;
    }

    multibyte_number& operator*=(Byte rhs)
    {
        Byte carry = 0;
        for (int i = 0; i < N; ++i)
        {
            std::tie(value_[i], carry) = mult_with_carry(value_[i], rhs, carry);
        }

        return *this;

    }
private:
    std::tuple<Byte, Byte> add_with_carry(Byte lhs, Byte rhs, Byte carry)
    {
        Converter conv;
        conv.result = static_cast<TwoBytes>(static_cast<TwoBytes>(lhs) + static_cast<TwoBytes>(rhs) +
                                            static_cast<TwoBytes>(carry));

        if (endianness::big_endian())
        {
            return std::make_tuple(conv.byte[1], conv.byte[0]);;
        }
        else
        {
            return std::make_tuple(conv.byte[0], conv.byte[1]);
        }
    }

    std::tuple<Byte, Byte> mult_with_carry(Byte lhs, Byte rhs, Byte carry)
    {
        Converter conv;
        conv.result = static_cast<TwoBytes>(static_cast<TwoBytes>(lhs) * static_cast<TwoBytes>(rhs)
                                            + static_cast<TwoBytes>(carry));

        if (endianness::big_endian())
        {
            return std::make_tuple(conv.byte[1], conv.byte[0]);
        }
        else
        {
            return std::make_tuple(conv.byte[0], conv.byte[1]);
        }
    }

    Data value_;
};

template <int N>
bool operator==(const multibyte_number<N> lhs, const multibyte_number<N> rhs)
{
    return lhs.equal_to(rhs);
}

template <int N>
std::ostream& operator<<(std::ostream& out, multibyte_number<N> v)
{
    return out << v.str();
}

template <int N>
multibyte_number<N> operator<<(const multibyte_number<N>& num, int shift)
{
    auto tmp{num};
    tmp <<= shift;
    return tmp;
}

template <int N>
multibyte_number<N> operator>>(const multibyte_number<N>& num, int shift)
{
    auto tmp{num};
    tmp >>= shift;
    return tmp;
}

#endif // include guard
