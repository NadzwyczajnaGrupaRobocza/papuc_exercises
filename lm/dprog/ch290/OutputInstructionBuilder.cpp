#include "OutputInstructionBuilder.hpp"

#include "throw_assert.hpp"
#include <iostream>
#include <regex>
#include <sstream>

namespace ltm
{
OutputInstructionBuilder::OutputInstructionBuilder()
    : InstructionBuilder(std::regex{"\\s+out \\((\\d)\\),([a-z])"})
{
}

Instruction
OutputInstructionBuilder::buildInstruction(const std::smatch& m) const
{
    throw_assert(m.size() == 3, "m contains: " << smatch_print(m));

    const Register outReg = registerNameToEnum(m[1]);
    const Register srcReg = registerNameToEnum(m[2]);
    throw_assert(isOutputRegister(outReg),
                 "invalid out register in output instruction");
    throw_assert(isInternalRegister(srcReg),
                 "invalid source register in output instruction");

    return {OperationType::output, outReg, 0u, srcReg};
}
}
