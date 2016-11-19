#pragma once
#include "Instruction.hpp"
#include <functional>
#include <unordered_map>
#include <vector>

namespace ltm
{

class Processor
{
public:
    using Program = std::vector<Instruction>;
    using OutputRegisters =
        std::unordered_map<Register, std::function<void(u8_t)>>;

    Processor(OutputRegisters);
    int runProgram(Program);

private:
    void runInstruction(const Program::value_type&);
    void runLoadInstruction(const Program::value_type&);
    void runOutputInstruction(const Program::value_type&);
    void runRotateLeftCyclicInstruction(const Program::value_type&);
    void runRotateRightCyclicInstruction(const Program::value_type&);
    void runDecrementAndJumpInstruction(const Program::value_type&);

    Program currentProgram{};
    Program::size_type counter{};
    int errorStatus{0};
    std::unordered_map<Register, u8_t> internalRegisters;
    OutputRegisters outputRegisters;
};
}
