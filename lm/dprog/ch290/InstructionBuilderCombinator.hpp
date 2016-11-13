#pragma once

#include "Instruction.hpp"
#include <functional>
#include <iosfwd>
#include <regex>
#include <string>
#include <vector>
#include <memory>
#include "InstructionBuilder.hpp"

namespace ltm
{
class InstructionBuilderCombinator
{
public:
    InstructionBuilderCombinator();
    std::vector<Instruction> process(std::istream&);

private:
    std::tuple<bool, Instruction>
    processSingleInstruction(const std::string&);
    bool shouldProcessAsEmpty(const std::string& line);
    bool shouldProcessAsInstruction(const std::string& line);

    using InstructionBuilderPtr = std::unique_ptr<InstructionBuilder>;
    using InstructionSet = std::vector<InstructionBuilderPtr>;

    const InstructionSet knownInstructions;
};
}
