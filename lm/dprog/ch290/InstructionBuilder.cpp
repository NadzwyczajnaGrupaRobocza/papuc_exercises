#include "InstructionBuilder.hpp"
#include <tuple>
#include <sstream>

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

std::string smatch_print(const std::smatch& m)
{
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
}
}
