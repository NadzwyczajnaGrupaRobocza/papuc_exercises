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
          return std::move(tmp);
      }()}
{
}

std::vector<Instruction>
InstructionBuilderCombinator::process(std::istream& in)
{
    std::vector<Instruction> iv;
    for (std::string line; std::getline(in, line);)
    {
        if (shouldProcessAsInstruction(line))
        {
            bool successfulMatch;
            Instruction matchedInstruction;
            std::tie(successfulMatch, matchedInstruction) =
                processSingleInstruction(line);
            if (successfulMatch)
            {
                iv.push_back(matchedInstruction);
            }
        }
        else if (shouldProcessAsEmpty(line))
        {
            
        }
        else
        {
            throw_assert(false, "should never end up here");
        }
        // else if (shouldProcessAsLabel(line))
        // {

        // }
        // else if (isEmptyLine(line))
        // {
        //     // nothing
        // }
        // else
        // {
        //     // error
        // }
    }

    return iv;
}

bool InstructionBuilderCombinator::shouldProcessAsInstruction(
    const std::string& line)
{
    return std::regex_match(line, std::regex{"\\s+\\w.*"});
}

bool InstructionBuilderCombinator::shouldProcessAsEmpty(
    const std::string& line)
{
    return std::regex_match(line, std::regex("\\s*"));
}

std::tuple<bool, Instruction>
InstructionBuilderCombinator::processSingleInstruction(
    const std::string& instruction)
{
    const auto& it =
        std::find_if(knownInstructions.begin(), knownInstructions.end(),
                     [&](const auto& instrBuilder) {
                         return instrBuilder->accepts(instruction);
                     });

    if (it != knownInstructions.end())
    {
        return (*it)->process(instruction);
    }

    return std::make_tuple(false, Instruction{});
}
}
