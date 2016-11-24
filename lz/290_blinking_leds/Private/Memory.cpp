#include "Memory.hpp"

namespace lz
{
void Memory::set_register_a(const Byte& reg)
{
    register_a = reg;
}

const Byte& Memory::get_register_a() const
{
    return register_a;
}
}
