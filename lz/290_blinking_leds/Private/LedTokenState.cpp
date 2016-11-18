#include "LedTokenState.hpp"
#include <ostream>

namespace lz
{
std::ostream& operator<<(std::ostream& os, const LedTokenState& state)
{
    os << "LedTokenState::";
    switch (state)
    {
    case LedTokenState::Recognize: os << "Recognize"; break;
    case LedTokenState::LedLdCommand: os << "LedLdCommand"; break;
    case LedTokenState::LedOutCommand: os << "LedOutCommand"; break;
    }
    return os;
}
}
