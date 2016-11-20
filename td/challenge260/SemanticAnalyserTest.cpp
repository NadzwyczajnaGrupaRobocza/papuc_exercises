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
    if (tokens.empty())
    {
      return {};
    }
    Instructions instructions;
    unsigned alreadyProcessedTokens = 0;
    while (tokens.size() - alreadyProcessedTokens % sizeOfInstruction && tokens.size() != alreadyProcessedTokens)
    {
      if (areTokensValidLdInstruction(tokens.cbegin() + alreadyProcessedTokens))
      {
        instructions.push_back({InstructionType::LdA, 0});
      }
      else if (areTokensValidOutInstruction(tokens.cbegin() + alreadyProcessedTokens))
      {
        instructions.push_back({InstructionType::OutA, 0});
      }
      else
      {
        throw InvalidSemantic{"Invalid instruction"};
      }
      alreadyProcessedTokens += sizeOfInstruction;
    }
    return instructions;
  }

private:
  static constexpr auto sizeOfInstruction = 3u;

  bool areTokensValidOutInstruction(Tokens::const_iterator begin)
  {
    return (begin++)->type == TokenType::Out
        && (begin++)->type == TokenType::ZeroWithBrackets
        && (begin++)->type == TokenType::A;
  }

  bool areTokensValidLdInstruction(Tokens::const_iterator begin)
  {
    return (begin++)->type == TokenType::Ld
        && (begin++)->type == TokenType::A
        && (begin++)->type == TokenType::Number8Bit;
  }
};

using namespace ::testing;

struct SemanticAnalyserTest : public Test
{
  SemanticAnalyser analyser;

  static constexpr Token createTokenWithZeroValue(TokenType type)
  {
    return{type, 0};
  }

  static constexpr Instruction createInstructionWithZeroValue(InstructionType type)
  {
    return{type, 0};
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

TEST_F(SemanticAnalyserTest, ShouldAcceptLdInstruction)
{
  Tokens tokens{createTokenWithZeroValue(TokenType::Ld),
                createTokenWithZeroValue(TokenType::A),
                createTokenWithZeroValue(TokenType::Number8Bit)};
  Instructions instructions{createInstructionWithZeroValue(InstructionType::LdA)};
  ASSERT_EQ(instructions, analyser.analyse(tokens));
}

TEST_F(SemanticAnalyserTest, ShouldAcceptOutInstruction)
{
  Tokens tokens{createTokenWithZeroValue(TokenType::Out),
                createTokenWithZeroValue(TokenType::ZeroWithBrackets),
                createTokenWithZeroValue(TokenType::A)};
  Instructions instructions{createInstructionWithZeroValue(InstructionType::OutA)};
  ASSERT_EQ(instructions, analyser.analyse(tokens));
}

TEST_F(SemanticAnalyserTest, ShouldNotAcceptInvalidInstruction)
{
  Tokens tokens{createTokenWithZeroValue(TokenType::Out),
                createTokenWithZeroValue(TokenType::Number8Bit),
                createTokenWithZeroValue(TokenType::A)};
  ASSERT_THROW(analyser.analyse(tokens), SemanticAnalyser::InvalidSemantic);
}

TEST_F(SemanticAnalyserTest, ShouldRejectInvalidLdInstruction)
{
  Tokens tokens{createTokenWithZeroValue(TokenType::Ld),
                createTokenWithZeroValue(TokenType::A),
                createTokenWithZeroValue(TokenType::Out)};
  ASSERT_THROW(analyser.analyse(tokens), SemanticAnalyser::InvalidSemantic);
}

TEST_F(SemanticAnalyserTest, ShouldAcceptOutInstructionFollowedByLd)
{
  Tokens tokens{createTokenWithZeroValue(TokenType::Out),
                createTokenWithZeroValue(TokenType::ZeroWithBrackets),
                createTokenWithZeroValue(TokenType::A),
                createTokenWithZeroValue(TokenType::Ld),
                createTokenWithZeroValue(TokenType::A),
                createTokenWithZeroValue(TokenType::Number8Bit)};
  Instructions instructions{createInstructionWithZeroValue(InstructionType::OutA), createInstructionWithZeroValue(InstructionType::LdA)};
  ASSERT_EQ(instructions, analyser.analyse(tokens));
}