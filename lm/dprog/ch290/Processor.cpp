#include "Processor.hpp"
#include "throw_assert.hpp"

Processor::Processor(OutputRegisters regs)
    : internalRegisters{{Register::reg_a, u8_t{0}}},
      outputRegisters{std::move(regs)}
{
}

int Processor::runProgram(Program prog)
{
    currentProgram = std::move(prog);
    counter = 0;
    errorStatus = 0;

    while (counter < currentProgram.size())
    {
        runInstruction(currentProgram[counter]);
    }

    return errorStatus;
}

void Processor::runInstruction(const Program::value_type& instr)
{
    switch (instr.operation)
    {
    case OperationType::load: runLoadInstruction(instr); break;
    case OperationType::output: runOutputInstruction(instr); break;
    default:
        throw_assert(0 == 1, "unhandled instuction - upgrade your CPU");
    }
}

void Processor::runLoadInstruction(const Program::value_type& instr)
{
    throw_assert(instr.operation == OperationType::load,
                 "wrong instruction runner");

    internalRegisters.at(instr.reg) = instr.value;

    counter++;
}

void Processor::runOutputInstruction(const Program::value_type& instr)
{
    throw_assert(instr.operation == OperationType::output,
                 "wrong instuction runner");

    outputRegisters.at(instr.reg)(internalRegisters.at(instr.srcReg));

    counter++;
}
