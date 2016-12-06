#pragma once

#include "Instruction.hpp"

#include <map>
#include <sstream>
#include <vector>

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

    using Instructions = std::vector<Instruction>;
    using LabelMapping = std::map<unsigned int, Instructions::const_iterator>;

    Instructions instructionsFromLabel;
    LabelMapping labelMapping;
    unsigned char b{0};
    std::ostream& out;
    LedState ledState;
    const std::size_t maxInstructions{10240};
};
