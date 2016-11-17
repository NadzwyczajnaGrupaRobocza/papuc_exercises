#pragma once

#include "Instruction.hpp"
#include "InstructionBuilder.hpp"
#include <functional>
#include <iosfwd>
#include <memory>
#include <regex>
#include <string>
#include <vector>

namespace ltm
{
class InstructionBuilderCombinator
{
public:
    using Program = std::vector<Instruction>;

    InstructionBuilderCombinator();
    Program process(std::istream&);

private:
    using InstructionBuilderPtr = std::unique_ptr<InstructionBuilder>;
    using InstructionSet = std::vector<InstructionBuilderPtr>;

    std::vector<std::string> preprocess(std::istream&);
    std::string preprocessIfLabel(const std::string&,
                                  std::vector<std::string>&);

    const InstructionSet knownInstructions;

    class Worker;
};
}
