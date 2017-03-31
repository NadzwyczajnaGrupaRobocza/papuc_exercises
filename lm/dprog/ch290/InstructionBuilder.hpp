#pragma once
#include "Instruction.hpp"
#include <regex>

namespace ltm
{

std::string smatch_print(const std::smatch& m);

class InstructionBuilder
{
public:
    virtual ~InstructionBuilder() = default;
    bool accepts(const std::string&) const;
    std::tuple<bool, Instruction> process(const std::string&) const;

protected:
    InstructionBuilder(std::regex);

private:
    const std::regex instructionPattern;
    virtual Instruction buildInstruction(const std::smatch&) const = 0;
};
}
