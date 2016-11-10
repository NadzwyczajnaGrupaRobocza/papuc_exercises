#include "gtest/gtest.h"

#include <stdexcept>

#include "Token.hpp"
#include "Instruction.hpp"

class SemanticAnalyser
{
public:
  class InvalidSemantic : public std::runtime_error
  {
  public:
    InvalidSemantic(const std::string& msg) : std::runtime_error{msg}
    {
    }
  };

  Instructions analyse(const Tokens& tokens)
  {
    if (tokens.empty() || tokens.size() == 3)
    {
      return {};
    }
    throw InvalidSemantic{"Invalid number of tokens"};
  }
};

using namespace ::testing;

struct SemanticAnalyserTest : public Test
{
  SemanticAnalyser analyser;
  static constexpr Token createTokenWithZeroValue(TokenType type)
  {
    return
    { type, 0};
  }
};

TEST_F(SemanticAnalyserTest, ShouldAcceptEmptyTokens)
{
  Tokens tokens{};
  Instructions instructions;
  ASSERT_EQ(instructions, analyser.analyse(tokens));
}

TEST_F(SemanticAnalyserTest, ShouldNotAcceptInvalidInstructionSet)
{
  Tokens tokens{createTokenWithZeroValue(TokenType::Ld)};
  ASSERT_THROW(analyser.analyse(tokens), SemanticAnalyser::InvalidSemantic);
}

TEST_F(SemanticAnalyserTest, ShouldNotAcceptValidLdInstructions)
{
  Tokens tokens{createTokenWithZeroValue(TokenType::Ld),
                createTokenWithZeroValue(TokenType::A),
                createTokenWithZeroValue(TokenType::Number8Bit)};
  ASSERT_NO_THROW(analyser.analyse(tokens));
}
