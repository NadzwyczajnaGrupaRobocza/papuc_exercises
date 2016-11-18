#pragma once
#include <iosfwd>

namespace lz
{
enum class
LedTokenState
{
    Recognize,
    LedLdCommand,
    LedOutCommand
};

std::ostream& operator<<(std::ostream&, const LedTokenState&);
}
