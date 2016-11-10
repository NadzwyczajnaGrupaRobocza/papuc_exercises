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