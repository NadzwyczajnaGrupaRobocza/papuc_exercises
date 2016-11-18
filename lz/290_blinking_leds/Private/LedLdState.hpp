#pragma once
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "LedTokenParser.hpp"

namespace lz
{
class IMemory;
class Register;
class LedLdState : public LedTokenParser
{
public:
    LedLdState(std::shared_ptr<IMemory>);
    LedTokenState parse(const LedToken&) override;

private:
    std::pair<std::string, int> splitToken(const LedToken&);
    std::shared_ptr<IMemory> memory;
    std::unordered_map<std::string, std::function<void(Register&&)>>
        save_in_register;
};
}
