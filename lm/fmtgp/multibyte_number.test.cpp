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
    multibyte_number<8> a1{std::array<Byte, 8>{1, 2, 3, 4, 5, 6, 7, 8}};
    multibyte_number<8> a2{std::array<Byte, 8>{1, 2, 3, 4, 5, 6, 7, 8}};
    multibyte_number<8> a3{std::array<Byte, 8>{1, 2, 3, 4, 5, 6, 7, 8}};

    multibyte_number<8> r1{std::array<Byte, 8>{0, 0, 0, 0, 0, 0, 0, 0}};
    multibyte_number<8> r2{std::array<Byte, 8>{0, 0, 0, 0, 0, 0, 0, 0}};
    multibyte_number<8> r3{std::array<Byte, 8>{0, 0, 0, 0, 0, 0, 0, 0}};

    a1 <<= 9;
    ASSERT_EQ(a1, r1);

    a2 <<= 8;
    ASSERT_EQ(a2, r2);

    // a3 <<= 300;
    // ASSERT_EQ(a3, r3);
}

TEST(multibyte_number, right_shift_works_on_bit_level__shifts_under_8_bits)
{
    //const auto value = 0x00FF00b0;
    const auto value = 0b10'00'0000'1111'1111'0000'0000'0011'0000;
    const auto result_shift_1 = 0b01'00'0000'0111'1111'1000'0000'0001'1000;
    const auto result_shift_2 = 0b00'10'0000'0011'1111'1100'0000'0000'1100;
    const auto result_shift_3 = 0b00'01'0000'0001'1111'1110'0000'0000'0110;
    const auto result_shift_4 = 0b00'00'1000'0000'1111'1111'0000'0000'0011;
    const auto result_shift_5 = 0b00'00'0100'0000'0111'1111'1000'0000'0001;
    const auto result_shift_6 = 0b00'00'0010'0000'0011'1111'1100'0000'0000;
    const auto result_shift_7 = 0b00'00'0001'0000'0001'1111'1110'0000'0000;

    multibyte_number<4> a_1{value};
    multibyte_number<4> a_2{value};
    multibyte_number<4> a_3{value};
    multibyte_number<4> a_4{value};
    multibyte_number<4> a_5{value};
    multibyte_number<4> a_6{value};
    multibyte_number<4> a_7{value};

    const multibyte_number<4> result_1{result_shift_1};
    const multibyte_number<4> result_2{result_shift_2};
    const multibyte_number<4> result_3{result_shift_3};
    const multibyte_number<4> result_4{result_shift_4};
    const multibyte_number<4> result_5{result_shift_5};
    const multibyte_number<4> result_6{result_shift_6};
    const multibyte_number<4> result_7{result_shift_7};

    a_1 >>= 1;
    a_2 >>= 2;
    a_3 >>= 3;
    a_4 >>= 4;
    a_5 >>= 5;
    a_6 >>= 6;
    a_7 >>= 7;

    ASSERT_EQ(a_1, result_1);
    ASSERT_EQ(a_2, result_2);
    ASSERT_EQ(a_3, result_3);
    ASSERT_EQ(a_4, result_4);
    ASSERT_EQ(a_5, result_5);
    ASSERT_EQ(a_6, result_6);
    ASSERT_EQ(a_7, result_7);
}

TEST(multibyte_number, right_shift_with_whole_bytes)
{
    const auto base = multibyte_number<4>(0x0A0B0C0D);
    auto a_1 = base;
    auto a_2 = base;
    auto a_3 = base;
    auto a_4 = base;
    const auto r_1 = multibyte_number<4>(0x000A0B0C);
    const auto r_2 = multibyte_number<4>(0x00000A0B);
    const auto r_3 = multibyte_number<4>(0x0000000A);
    const auto r_4 = multibyte_number<4>(0x00000000);

    ASSERT_EQ(a_1, base);
    a_1 >>=  8;
    a_2 >>= 16;
    a_3 >>= 24;
    a_4 >>= 32;

    ASSERT_EQ(a_1, r_1);
    ASSERT_EQ(a_2, r_2);
    ASSERT_EQ(a_3, r_3);
    ASSERT_EQ(a_4, r_4);
}


TEST(multibyte_number, right_shift__mixed_shift)
{
    auto a =       multibyte_number<4>{0b10'00'0000'1111'1111'0000'0000'0011'0000};
    const auto r = multibyte_number<4>{0b00'00'0000'0100'0000'0111'1111'1000'0000};

    a >>= 9;

    ASSERT_EQ(a, r);
}
