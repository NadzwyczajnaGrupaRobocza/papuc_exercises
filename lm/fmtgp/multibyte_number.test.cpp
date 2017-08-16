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

    multibyte_number<16> r2{std::array<Byte, 16>{3, 3, 5, 5, 7, 7, 9, 9, 11, 11, 13, 13, 15, 15, 17, 17}};

    a += b;
    a1 += a2;

    a1 += a3;

    ASSERT_EQ(a, r);
    ASSERT_EQ(a1, r2);
}

TEST(multibyte_number, left_shift_asign_operator_basic_operation)
{
    using Byte = multibyte_number<16>::Byte;
    multibyte_number<16> a{std::array<Byte, 16>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 20}};
    multibyte_number<16> r{   std::array<Byte, 16>{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 20, 0}};

    a <<= 1;

    ASSERT_EQ(a, r);
}

TEST(multibyte_number, left_shift_asign_operator_no_op_when_non_positive_shift)
{
    using Byte = multibyte_number<8>::Byte;
    multibyte_number<8> a{std::array<Byte, 8>{1, 2, 3, 4, 5, 6, 7, 8}};
    const auto copy = a;

    a <<= 0;
    ASSERT_EQ(a, copy);

    a <<= -3;
    ASSERT_EQ(a, copy);
}

TEST(multibyte_number, left_shift_asign_operator_all_zeros_when_shift_greater_than_length)
{
    using Byte = multibyte_number<8>::Byte;
    multibyte_number<8> a{std::array<Byte, 8>{1, 2, 3, 4, 5, 6, 7, 8}};
    multibyte_number<8> r{std::array<Byte, 8>{0, 0, 0, 0, 0, 0, 0, 0}};

    a <<= 9;
    ASSERT_EQ(a, r);
}
