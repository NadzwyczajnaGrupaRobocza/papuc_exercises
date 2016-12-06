#include "LedOutState.hpp"

#include <bitset>
#include <gsl/gsl_assert>
#include <iostream>

#include "Byte.hpp"
#include "IMemory.hpp"
#include "LedToken.hpp"

namespace lz
{
LedOutState::LedOutState(std::shared_ptr<const IMemory> mem) : memory{mem}
{
}

LedTokenState LedOutState::parse(const LedToken& token)
{
    validateOutCommand(token);
    printRegisterA();
    return LedTokenState::Recognize;
}

void LedOutState::validateOutCommand(const LedToken& token) const
{
    const auto splitted = token.split<std::string, std::string>(',');
    Expects(splitted.first == "(0)");
    Expects(splitted.second == "a");
}

void LedOutState::printRegisterA() const
{
    std::cout << std::bitset<8>{memory->get_register_a().value()}.to_string('.',
                                                                            '*')
              << "\n";
}
}
