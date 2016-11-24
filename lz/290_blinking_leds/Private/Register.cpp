#include "Register.hpp"

namespace lz
{
Register::Register() : _value{0}
{
}

Register::Register(std::uint8_t v) : _value{v}
{
}

const std::uint8_t& Register::value() const
{
    return _value;
}

bool operator==(const Register& lhs, const Register& rhs)
{
    return lhs.value() == rhs.value();
}
}
