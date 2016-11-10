#include "gtest/gtest.h"

#include "Token.hpp"

class SemanticAnalyser
{
public:
  bool analyse(const Tokens&)
  {
    return true;
  }
};

TEST(SemanticAnalyserTest, ShouldAcceptEmptyTokens)
{
  SemanticAnalyser analyser;
  Tokens tokens{{}};
  ASSERT_TRUE(analyser.analyse(tokens));
}