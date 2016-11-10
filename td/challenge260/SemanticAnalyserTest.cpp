#include "gtest/gtest.h"

class SemanticAnalyser
{
public:
  bool analyse(const std::string&)
  {
    return true;
  }
};

TEST(SemanticAnalyserTest, D)
{
  SemanticAnalyser analyser;
  ASSERT_TRUE(analyser.analyse(""));
}