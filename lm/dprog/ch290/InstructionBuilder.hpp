#pragma once
#include "Instruction.hpp"
#include <regex>

namespace ltm
{

inline std::string smatch_print(const std::smatch& m)
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
