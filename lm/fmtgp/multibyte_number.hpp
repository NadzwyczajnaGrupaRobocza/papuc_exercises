#ifndef MULTIBYTE_NUMBER_HPP
#define MULTIBYTE_NUMBER_HPP

#include <array>
#include <cstdint>
#include <iterator>
#include <tuple>
#include <iomanip>

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
    //multibyte_number(const std::string& text);

    multibyte_number(std::array<Byte, N> init)
        : value_{}
    {
        std::copy(init.rbegin(), init.rend(), value_.begin());
    }

    const auto& value() const
    {
        return value_;
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
private:
    using TwoBytes = std::uint16_t;

    std::tuple<Byte, Byte> add_with_carry(Byte lhs, Byte rhs, Byte carry)
    {
        union
        {
            TwoBytes result;
            Byte byte[2];
        } conv{};
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

    std::array<Byte, N> value_;
};

template <int N>
bool operator==(const multibyte_number<N> lhs, const multibyte_number<N> rhs)
{
    return lhs.equal_to(rhs);
}

template <int N>
std::ostream& operator<<(std::ostream& out, multibyte_number<N> v)
{
    auto f{out.flags()};
    out << v.value().size() << N << " ";
    out << "0x" << std::hex << std::setw(2) << std::setfill('0');
    for (int i = static_cast<int>(v.value().size() - 1);
         i >= 0;
         --i)
    {
        out << std::setw(2) << static_cast<int>(v.value()[i]);
    }

    out.flags(f);
    return out;
}

#endif // include guard
