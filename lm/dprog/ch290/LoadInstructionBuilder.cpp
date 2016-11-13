#include "LoadInstructionBuilder.hpp"
#include "throw_assert.hpp"
#include <iostream>
#include <regex>
#include <sstream>

namespace ltm
{
LoadInstructionBuilder::LoadInstructionBuilder()
    : InstructionBuilder(std::regex{"\\s+ld ([a-z]),(\\d+)"})
{
}

Instruction
LoadInstructionBuilder::buildInstruction(const std::smatch& m) const
{
    throw_assert(m.size() == 3, "m contains: " << [](const std::smatch& m) {
        std::stringstream content;
        for (auto i = 0u; i < m.size(); ++i)
        {
            if (i > 0u)
            {
                content << " ";
            }
            content << "m[" << i << "]=" << m[i];
        }
        return content.str();
    }(m));

    const std::string registerName = m[1];
    const std::string valueStr = m[2];

    throw_assert(isValidInternalRegisterName(registerName),
                 "addressing unknown register");

    auto reg = registerNameToEnum(registerName);

    int value = std::stoi(valueStr);

    throw_assert((value >= std::numeric_limits<u8_t>::lowest() and
                  value <= std::numeric_limits<u8_t>::max()),
                 "invalid value in op");

    return {OperationType::load, reg, static_cast<u8_t>(value),
            Register::INVALID};
}
}
