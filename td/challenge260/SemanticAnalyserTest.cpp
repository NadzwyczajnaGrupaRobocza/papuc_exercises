#include "gtest/gtest.h"

#include "Token.hpp"

class SemanticAnalyser
{
public:
  bool analyse(const Tokens& tokens)
  {
    return tokens.empty();
  }
};

constexpr Token createTokenWithZeroValue(TokenType type)
{
  return {type, 0};
}

TEST(SemanticAnalyserTest, ShouldAcceptEmptyTokens)
{
  SemanticAnalyser analyser;
  Tokens tokens{};
  ASSERT_TRUE(analyser.analyse(tokens));
}

TEST(SemanticAnalyserTest, ShouldNotAcceptInvalidInstructionSet)
{
  SemanticAnalyser analyser;
  Tokens tokens{createTokenWithZeroValue(TokenType::Ld)};
  ASSERT_FALSE(analyser.analyse(tokens));
}