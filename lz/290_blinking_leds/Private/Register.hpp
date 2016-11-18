#pragma once
#include <cstdint>

namespace lz
{
class Register
{
public:
    Register();
    explicit Register(std::uint8_t);
    const std::uint8_t& value() const;

    friend bool operator==(const Register&, const Register&);

private:
    std::uint8_t _value;
};
}
