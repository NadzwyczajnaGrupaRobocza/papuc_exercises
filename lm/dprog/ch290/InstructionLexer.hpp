#pragma once

#include "Instruction.hpp"
#include <vector>
#include <iosfwd>
#include <string>
#include <regex>
#include <functional>

class InstructionLexer
{
public:
    InstructionLexer();
    std::vector<Instruction> lex(std::istream&);
private:
    Instruction processSingleInstruction(const std::string&);
    bool shouldProcessLine(const std::string& line);

    using InstructionBuilder = std::function<Instruction(const std::smatch&)>;
    using PatternToBuilderRel = std::pair<std::regex, InstructionBuilder>;
    using InstructionSet = std::vector<PatternToBuilderRel>;

    const InstructionSet knownInstructions;
};
