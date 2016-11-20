#include "gtest/gtest.h"

#include "Instruction.hpp"

class LedController
{
public:
  void runProgram(const Instructions &)
  {
  }

};

TEST(LedControllerTest, ShouldCreate)
{
  LedController controller;
  controller.runProgram(Instructions{});
}