#pragma once

#include <string>
#include <stdexcept>
#include "boost/tokenizer.hpp"


class InstructionParser
{
public:
  class UnknownInstruction : public std::runtime_error
  {
  public:
    UnknownInstruction(const std::string& msg) : std::runtime_error{msg}
    {}
  };

  class MissingArgument : public std::runtime_error
  {
  public:
    MissingArgument(const std::string& msg) : std::runtime_error{msg}
    {}
  };


  void parseInstructions(const std::string& instructions);

private:
  void parseInstruction(const std::string& instruction);
  std::string trimWhitespacesOnFront(const std::string& instruction);
};