#include <gtest/gtest.h>

#include "multibyte_number.hpp"

TEST(multibyte_number, utils_endianness_checker)
{
    ASSERT_FALSE(endianness::big_endian());
}

TEST(multibyte_number, plus_equals_works_with_4_byte_values)
{
    multibyte_number<4> a{0x01010101};
    multibyte_number<4> b{0x01020102};
    multibyte_number<4> expected_result{0x02030203};

    a += b;
    ASSERT_EQ(a, expected_result);
}

TEST(multibyte_number, initialization_arbitrary_length)
{
    using Byte = multibyte_number<16>::Byte;
    multibyte_number<16> a1{std::array<Byte, 16>{1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}};
    multibyte_number<16> a2{std::array<Byte, 16>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
    multibyte_number<16> a3{std::array<Byte, 16>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}};
    multibyte_number<16> a{std::array<Byte, 16>{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xA}};
    multibyte_number<16> b{std::array<Byte, 16>{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    multibyte_number<16> r{std::array<Byte, 16>{0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xA}};

    a += b;
    a1 += a2;

    std::cout << a << '\n';
    std::cout << b << '\n';

    std::cout << a1 << '\n';
    std::cout << a3 << '\n';
    a1 += a3;
    std::cout << a1 << '\n';

    ASSERT_EQ(a, r);
}
