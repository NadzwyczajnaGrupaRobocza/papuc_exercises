#include "Byte.hpp"
#include <gtest/gtest.h>

namespace lz
{
TEST(ByteTest, construct)
{
    Byte reg_a{45};
    EXPECT_EQ(45, reg_a.value());

    Byte reg_b;
    EXPECT_EQ(0, reg_b.value());
}

TEST(ByteTest, copy)
{
    Byte reg_a{45};
    Byte reg_copy_a = reg_a;
    EXPECT_EQ(reg_a, reg_copy_a);
}

TEST(ByteTest, assign)
{
    Byte reg_a{45};
    reg_a = Byte{89};
    EXPECT_EQ(89, reg_a.value());
}

TEST(ByteTest, scope)
{
    Byte min{0};
    Byte max{255};

    EXPECT_EQ(0, min.value());
    EXPECT_EQ(255, max.value());
}
}
