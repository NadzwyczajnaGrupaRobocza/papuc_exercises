#pragma once

#include "InstructionBuilder.hpp"

namespace ltm
{
class OutputInstructionBuilder : public InstructionBuilder
{
public:
    OutputInstructionBuilder();

private:
    Instruction buildInstruction(const std::smatch& m) const;
};
}
