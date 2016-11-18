#include "Memory.hpp"

namespace lz
{
void Memory::set_register_a(const Register& reg)
{
    register_a = reg;
}

const Register& Memory::get_register_a() const
{
    return register_a;
}
}
