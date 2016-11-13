#pragma once

#include "InstructionBuilder.hpp"

namespace ltm
{
class DecrementAndJumpIfNonZeroInstructionBuilder : public InstructionBuilder
{
public:
    DecrementAndJumpIfNonZeroInstructionBuilder();

private:
    Instruction buildInstruction(const std::smatch& m) const;
};
}
