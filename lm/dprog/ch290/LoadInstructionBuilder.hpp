#pragma once
#include "InstructionBuilder.hpp"


namespace ltm
{
class LoadInstructionBuilder : public InstructionBuilder
{
public:
    LoadInstructionBuilder();

private:
    virtual Instruction
    buildInstruction(const std::smatch& m) const override;
};
}
