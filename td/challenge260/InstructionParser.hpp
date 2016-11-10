#pragma once

#include <string>
#include <stdexcept>
#include "Token.hpp"


class InstructionParser
{
public:
  class UnknownInstruction : public std::runtime_error
  {
  public:
    UnknownInstruction(const std::string& msg) : std::runtime_error{msg}
    {}
  };

  Tokens parseInstructions(const std::string& instructions);

private:
  Tokens parseInstruction(const std::string& instruction);
  std::string trimWhitespacesOnFront(const std::string& instruction);
};