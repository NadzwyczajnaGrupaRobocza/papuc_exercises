#include "LedLdState.hpp"

#include <gsl/gsl_assert>
#include <iostream>

#include "Byte.hpp"
#include "IMemory.hpp"
#include "LedToken.hpp"

namespace lz
{
LedLdState::LedLdState(std::shared_ptr<IMemory> mem) : memory{mem}
{
    save_in_register.emplace("a", [this](Byte&& reg) {
        this->memory->set_register_a(std::move(reg));
    });
}

LedTokenState LedLdState::parse(const LedToken& token)
{
    const auto splitted = token.split<std::string, int>(',');
    const auto& reg = splitted.first;
    const auto& value = splitted.second;

    Expects(value >= 0 && value <= 255);

    try
    {
        save_in_register.at(reg)(Byte{static_cast<uint8_t>(value)});
    }
    catch (std::out_of_range&)
    {
        std::cerr << "Register is not found.\n";
        throw;
    }

    return LedTokenState::Recognize;
}
}
