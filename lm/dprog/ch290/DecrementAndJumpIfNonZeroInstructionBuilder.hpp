#pragma once

#include "InstructionBuilder.hpp"

namespace ltm
{
class DecrementAndJumpInstructionBuilder : public InstructionBuilder
{
public:
    DecrementAndJumpInstructionBuilder();

private:
    Instruction buildInstruction(const std::smatch& m) const;
};
}
