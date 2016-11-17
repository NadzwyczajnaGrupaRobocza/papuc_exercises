#include "InstructionBuilderCombinator.hpp"
#include "DecrementAndJumpIfNonZeroInstructionBuilder.hpp"
#include "LoadInstructionBuilder.hpp"
#include "OutputInstructionBuilder.hpp"
#include "RotateLeftCyclicInstructionBuilder.hpp"
#include "RotateRightCyclicInstructionBuilder.hpp"
#include "throw_assert.hpp"
#include <iostream>
#include <istream>

namespace ltm
{

InstructionBuilderCombinator::InstructionBuilderCombinator()
    : knownInstructions{[this]() {
          InstructionSet tmp;
          tmp.push_back(std::make_unique<LoadInstructionBuilder>());
          tmp.push_back(std::make_unique<OutputInstructionBuilder>());
          tmp.push_back(
              std::make_unique<RotateLeftCyclicInstructionBuilder>());
          tmp.push_back(
              std::make_unique<RotateRightCyclicInstructionBuilder>());
          tmp.push_back(std::make_unique<
                        DecrementAndJumpIfNonZeroInstructionBuilder>());
          return tmp;
      }()}
{
}

class InstructionBuilderCombinator::Worker
{
public:
    Worker(const InstructionSet& instructionSetInit,
           std::vector<std::string>& inInit)
        : instructionSet{instructionSetInit}, in{inInit}, program{},
          labelToLoc{}, currentLine{0}
    {
    }

    Program process();

private:
    std::tuple<bool, Instruction>
    processSingleInstruction(const std::string&);
    void processLabel(const std::string&);
    bool shouldProcessAsEmpty(const std::string&);
    bool shouldProcessAsLabel(const std::string&);
    bool shouldProcessAsInstruction(const std::string&);

    const InstructionSet& instructionSet;
    std::vector<std::string>& in;

    Program program;
    std::map<std::string, Program::size_type> labelToLoc;
    int currentLine;
};

InstructionBuilderCombinator::Program
InstructionBuilderCombinator::process(std::istream& in)
{
    std::vector<std::string> progLines = preprocess(in);
    Worker w{knownInstructions, progLines};
    return w.process();
}

std::vector<std::string>
InstructionBuilderCombinator::preprocess(std::istream& in)
{
    std::vector<std::string> numToLabel{};
    std::vector<std::string> lines{};
    for (std::string line; std::getline(in, line);)
    {
        lines.push_back(preprocessIfLabel(line, numToLabel));
    }

    return lines;
}

std::string InstructionBuilderCombinator::preprocessIfLabel(
    const std::string& line, std::vector<std::string>& labels)
{
    std::smatch m;
    if (std::regex_match(line, m, std::regex{"(\\w+):"}))
    {
        std::string label = m[1];
        auto it = std::find(labels.begin(), labels.end(), label);
        if (it == labels.end())
        {
            const auto label_pos = labels.size();
            labels.push_back(label);
            return std::to_string(label_pos) + ":";
        }
        else
        {
            const auto label_pos = std::distance(labels.begin(), it);
            return std::to_string(label_pos) + ":";
        }
    }
    else if (std::regex_match(line, m,
                              std::regex{"\\s+djnz ([a-z]) ([0-9]+)"}))
    {
        std::string label = m[1];
        auto it = std::find(labels.begin(), labels.end(), label);
        if (it == labels.end())
        {
            const auto label_pos = labels.size();
            labels.push_back(label);
            return " djnz " + std::to_string(label_pos);
        }
        else
        {
            const auto label_pos = std::distance(labels.begin(), it);
            return " djnz " + std::to_string(label_pos);
        }
    }
    else
    {
        return line;
    }
}

InstructionBuilderCombinator::Program
InstructionBuilderCombinator::Worker::process()
{
    for (const std::string& line : in)
    {
        currentLine++;
        if (shouldProcessAsInstruction(line))
        {
            bool successfulMatch;
            Instruction matchedInstruction;
            std::tie(successfulMatch, matchedInstruction) =
                processSingleInstruction(line);
            if (successfulMatch)
            {
                program.push_back(matchedInstruction);
            }
        }
        else if (shouldProcessAsLabel(line))
        {
            processLabel(line);
        }
        else if (shouldProcessAsEmpty(line))
        {
        }
        else
        {
            throw_assert(false, "should never end up here");
        }
    }

    return program;
}

bool InstructionBuilderCombinator::Worker::shouldProcessAsInstruction(
    const std::string& line)
{
    return std::regex_match(line, std::regex{"\\s+\\w.*"});
}

bool InstructionBuilderCombinator::Worker::shouldProcessAsLabel(
    const std::string& line)
{
    return std::regex_match(line, std::regex{"[a-zA-Z]+:"});
}

bool InstructionBuilderCombinator::Worker::shouldProcessAsEmpty(
    const std::string& line)
{
    return std::regex_match(line, std::regex("\\s*"));
}

std::tuple<bool, Instruction>
InstructionBuilderCombinator::Worker::processSingleInstruction(
    const std::string& instruction)
{
    const auto& it =
        std::find_if(instructionSet.begin(), instructionSet.end(),
                     [&](const auto& instrBuilder) {
                         return instrBuilder->accepts(instruction);
                     });

    if (it != instructionSet.end())
    {
        return (*it)->process(instruction);
    }

    return std::make_tuple(false, Instruction{});
}

void InstructionBuilderCombinator::Worker::processLabel(
    const std::string& label)
{
    throw_assert(label[label.size() - 1] == ':',
                 "processing invalid label");

    const std::string labelTrim = [](const std::string& s) {
        auto copy = s;
        copy.pop_back();
        return copy;
    }(label);

    throw_assert(labelToLoc.count(labelTrim) == 0,
                 "redefinition of label " << labelTrim << " at "
                                          << currentLine);

    labelToLoc.emplace(labelTrim, program.size());
}
}
