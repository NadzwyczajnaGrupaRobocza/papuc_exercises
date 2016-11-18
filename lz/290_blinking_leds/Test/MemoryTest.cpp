#include "Memory.hpp"
#include <gtest/gtest.h>

namespace lz
{
TEST(MemoryTest, setAndGetRegister)
{
    Memory memory{};
    memory.set_register_a(Register{255});
    EXPECT_EQ(Register{255}, memory .get_register_a());
}
}
