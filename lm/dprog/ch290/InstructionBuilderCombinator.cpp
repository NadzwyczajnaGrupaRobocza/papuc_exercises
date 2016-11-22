#include "InstructionBuilderCombinator.hpp"
#include "DecrementAndJumpInstructionBuilder.hpp"
#include "LoadInstructionBuilder.hpp"
#include "OutputInstructionBuilder.hpp"
#include "RotateLeftCyclicInstructionBuilder.hpp"
#include "RotateRightCyclicInstructionBuilder.hpp"
#include "throw_assert.hpp"
#include <iostream>
#include <istream>
#include <map>
#include <tuple>

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
          tmp.push_back(
              std::make_unique<DecrementAndJumpInstructionBuilder>());
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
    void postprocessLabels();

    const InstructionSet& instructionSet;
    std::vector<std::string>& in;

    Program program;
    std::map<u8_t, Program::size_type> labelToLoc;
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
                              std::regex{"\\s+djnz ([a-z]) (\\w+)"}))
    {
        const std::string label = m[2];
        const std::string reg = m[1];
        auto it = std::find(labels.begin(), labels.end(), label);
        if (it == labels.end())
        {
            const auto label_pos = labels.size();
            labels.push_back(label);
            return " djnz " + reg + " " + std::to_string(label_pos);
        }
        else
        {
            const auto label_pos = std::distance(labels.begin(), it);
            return " djnz " + reg + " " + std::to_string(label_pos);
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
            throw_assert(false, "unknown instruction in line "
                                    << currentLine << ": " << line);
        }
    }

    postprocessLabels();

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
    return std::regex_match(line, std::regex{"[0-9]+:"});
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
    const std::string& line)
{
    throw_assert(line[line.size() - 1] == ':', "processing invalid label");

    const std::string labelStr = [](const std::string& s) {
        auto copy = s;
        copy.pop_back();
        return copy;
    }(line);

    const u8_t label = static_cast<u8_t>(std::stoi(labelStr));

    throw_assert(labelToLoc.count(label) == 0, "redefinition of label "
                                                   << label << " at "
                                                   << currentLine);

    labelToLoc.emplace(label, program.size());
}

void InstructionBuilderCombinator::Worker::postprocessLabels()
{
    for (auto& instr : program)
    {
        if (instr.operation == OperationType::decrementAndJump)
        {
            instr.value = static_cast<u8_t>(labelToLoc.at(instr.value));
        }
    }
}
}
