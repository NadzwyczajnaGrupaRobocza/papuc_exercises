#pragma once

#include "InstructionBuilder.hpp"

namespace ltm
{
class RotateLeftCyclicInstructionBuilder : public InstructionBuilder
{
public:
    RotateLeftCyclicInstructionBuilder();

private:
    Instruction buildInstruction(const std::smatch& m) const;
};
}
