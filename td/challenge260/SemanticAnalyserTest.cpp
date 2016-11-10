#include "gtest/gtest.h"

#include "Token.hpp"

class SemanticAnalyser
{
public:
  bool analyse(const Tokens& tokens)
  {
    return tokens.empty() || tokens.size() == 3;
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
  ASSERT_TRUE(analyser.analyse(tokens));
}

TEST_F(SemanticAnalyserTest, ShouldNotAcceptInvalidInstructionSet)
{
  Tokens tokens{createTokenWithZeroValue(TokenType::Ld)};
  ASSERT_FALSE(analyser.analyse(tokens));
}

TEST_F(SemanticAnalyserTest, ShouldAcceptLdInstruction)
{
  Tokens tokens{createTokenWithZeroValue(TokenType::Ld),
                createTokenWithZeroValue(TokenType::A),
                createTokenWithZeroValue(TokenType::Number8Bit)};
  ASSERT_TRUE(analyser.analyse(tokens));
}

TEST_F(SemanticAnalyserTest, ShouldAcceptOutInstruction)
{
  Tokens tokens{createTokenWithZeroValue(TokenType::Out),
                createTokenWithZeroValue(TokenType::ZeroWithBrackets),
                createTokenWithZeroValue(TokenType::A)};
  ASSERT_TRUE(analyser.analyse(tokens));
}