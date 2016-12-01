#include "Byte.hpp"

namespace lz
{
Byte::Byte() : _value{0}
{
}

Byte::Byte(const std::uint8_t v) : _value{v}
{
}

const std::uint8_t& Byte::value() const
{
    return _value;
}

bool operator==(const Byte& lhs, const Byte& rhs)
{
    return lhs.value() == rhs.value();
}
}
