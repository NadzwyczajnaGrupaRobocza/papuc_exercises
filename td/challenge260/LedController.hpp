#pragma once

#include "Instruction.hpp"

#include <sstream>

class LedController
{
public:
    explicit LedController(std::ostream& stream);
    void runProgram(const Instructions& instructions);

private:
    class LedState
    {
    public:
        const LedState& operator=(unsigned char);
        operator std::string() const;
        void rlca();

    private:
        unsigned char ledState{0};
    };

    std::ostream& out;
    LedState ledState;

    void runInstruction(const Instruction& instruction);
    static std::string getLedStateFromInteger(LedState value);
};
