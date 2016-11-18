#include "Register.hpp"
#include <gtest/gtest.h>

namespace lz
{
TEST(RegisterTest, construct)
{
    Register reg_a{static_cast<std::uint8_t>(45)};
    EXPECT_EQ(45, reg_a.value());

    Register reg_b;
    EXPECT_EQ(0, reg_b.value());
}

TEST(RegisterTest, copy)
{
    Register reg_a{static_cast<std::uint8_t>(45)};
    Register reg_copy_a = reg_a;
    EXPECT_EQ(reg_a, reg_copy_a);
}

TEST(RegisterTest, assign)
{
    Register reg_a{static_cast<std::uint8_t>(45)};
    reg_a = Register{static_cast<std::uint8_t>(89)};
    EXPECT_EQ(89, reg_a.value());
}

TEST(RegisterTest, scope)
{
    Register min{0};
    Register max{255};

    EXPECT_EQ(0, min.value());
    EXPECT_EQ(255, max.value());
}
}
