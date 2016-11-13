#pragma once

#include "InstructionBuilder.hpp"

namespace ltm
{
class RotateRightCyclicInstructionBuilder : public InstructionBuilder
{
public:
    RotateRightCyclicInstructionBuilder();

private:
    Instruction buildInstruction(const std::smatch& m) const;
};
}
