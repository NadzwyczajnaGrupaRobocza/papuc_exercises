#include "InstructionBuilder.hpp"
#include <tuple>

namespace ltm
{
InstructionBuilder::InstructionBuilder(std::regex pattern)
    : instructionPattern{std::move(pattern)}
{
}

bool InstructionBuilder::accepts(const std::string& instruction) const
{
    return std::regex_match(instruction, instructionPattern);
}

std::tuple<bool, Instruction>
InstructionBuilder::process(const std::string& instruction) const
{
    std::smatch m;
    if (std::regex_match(instruction, m, instructionPattern))
    {
        return std::make_tuple(true, buildInstruction(m));
    }

    return std::make_tuple(false, Instruction{});
}
}
