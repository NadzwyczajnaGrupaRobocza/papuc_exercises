#pragma once
#include <cstdint>

namespace lz
{
class Byte
{
public:
    Byte();
    explicit Byte(std::uint8_t);
    const std::uint8_t& value() const;

    friend bool operator==(const Byte&, const Byte&);

private:
    std::uint8_t _value;
};
}
