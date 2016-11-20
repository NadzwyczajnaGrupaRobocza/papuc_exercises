#pragma once

#include "Instruction.hpp"

#include <sstream>

class LedController
{
public:
    explicit LedController(std::ostream& stream);
    void runProgram(const Instructions& instructions);

private:
    std::ostream& out;
    std::string ledState{getLedStateFromInteger(0)};

    void runInstruction(const Instruction& instruction);
    static std::string getLedStateFromInteger(unsigned value);
};
