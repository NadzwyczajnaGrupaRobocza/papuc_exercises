#include "LedOutState.hpp"

#include <bitset>
#include <gsl/gsl_assert>
#include <iostream>

#include "IMemory.hpp"
#include "LedToken.hpp"
#include "Register.hpp"

namespace lz
{
LedOutState::LedOutState(std::shared_ptr<const IMemory> mem) : memory{mem}
{
}

LedTokenState LedOutState::parse(const LedToken& token)
{
    const auto splitted = token.split<std::string, std::string>(',');

    Expects(splitted.first == "(0)");
    Expects(splitted.second == "a");

    std::cout << std::bitset<8>{memory->get_register_a().value()}.to_string('.',
                                                                            '*')
              << "\n";

    return LedTokenState::Recognize;
}
}
