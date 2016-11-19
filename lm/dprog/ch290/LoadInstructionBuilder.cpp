#include "LoadInstructionBuilder.hpp"
#include "throw_assert.hpp"
#include <iostream>
#include <regex>
#include <sstream>
#include "Value.hpp"

namespace ltm
{
LoadInstructionBuilder::LoadInstructionBuilder()
    : InstructionBuilder(std::regex{"\\s+ld ([a-z]),(\\d+)"})
{
}

Instruction
LoadInstructionBuilder::buildInstruction(const std::smatch& m) const
{
    throw_assert(m.size() == 3, "m contains: " << smatch_print(m));

    const std::string registerName = m[1];
    const std::string valueStr = m[2];

    throw_assert(isValidInternalRegisterName(registerName),
                 "addressing unknown register");

    auto reg = registerNameToEnum(registerName);

    return {OperationType::load, reg, Value{valueStr},
            Register::INVALID};
}
}
