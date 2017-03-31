#pragma once
#include "throw_assert.hpp"
#include <string>

namespace ltm
{
using u8_t = unsigned char;
static_assert(sizeof(u8_t) == 1, "epic fail");

class Value
{
public:
    Value(const std::string& valueStr) : value{std::stoi(valueStr)}
    {
        throw_assert((value >= std::numeric_limits<u8_t>::lowest() and
                      value <= std::numeric_limits<u8_t>::max()),
                     "invalid value in op");
    }

    operator u8_t()
    {
        return static_cast<u8_t>(value);
    }

private:
    int value;
};
}
