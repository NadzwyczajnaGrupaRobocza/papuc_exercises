#pragma once

#include "Instruction.hpp"

#include <list>
#include <map>
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
        void rrca();
        std::string to_string() const;

    private:
        unsigned char ledState{0};
    };

    void runInstruction(const Instruction& instruction);
    static std::string getLedStateFromInteger(LedState value);
    void doDjnz(unsigned char);

    using InstructionsFromLabel = std::list<Instruction>;
    using LabelMapping =
        std::map<unsigned int, InstructionsFromLabel::const_iterator>;

    InstructionsFromLabel instructionsFromLabel;
    LabelMapping labelMapping;
    unsigned char b{0};
    std::ostream& out;
    LedState ledState;
};
