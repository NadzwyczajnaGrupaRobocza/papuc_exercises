#include "Memory.hpp"
#include <gtest/gtest.h>

namespace lz
{
TEST(MemoryTest, setAndGetByte)
{
    Memory memory{};
    EXPECT_EQ(Byte{0}, memory.get_register_a());
    memory.set_register_a(Byte{255});
    EXPECT_EQ(Byte{255}, memory.get_register_a());
    memory.set_register_a(Byte{5});
    EXPECT_EQ(Byte{5}, memory.get_register_a());
    memory.set_register_a(Byte{0});
    EXPECT_EQ(Byte{0}, memory.get_register_a());
    memory.set_register_a(Byte{16});
    EXPECT_EQ(Byte{16}, memory.get_register_a());
}
}
