#include "gmock/gmock.h"

#include <sstream>

#include "Instruction.hpp"

class LedController
{
public:
  explicit LedController(std::ostream &stream) :
    out{stream}
  {
  }

  void runProgram(const Instructions &instructions)
  {
    for (const auto &instruction : instructions)
    {
      runInstruction(instruction);
    }
  }



private:
  std::ostream &out;

  void runInstruction(const Instruction & instruction)
  {
    if (instruction.type == InstructionType::OutA)
    {
      out << "........\n";
    }
  }

};

static constexpr Instruction createInstructionWithZeroValue(InstructionType type)
{
  return{type, 0};
}

using namespace ::testing;

class LedControllerTest : public Test
{
public:
  std::stringstream stream;
  LedController controller{stream};
};

TEST_F(LedControllerTest, OutInstructionShouldPrintLedState)
{
  controller.runProgram(Instructions{createInstructionWithZeroValue(InstructionType::OutA)});

  EXPECT_THAT(stream.str(), Eq("........\n"));
}

TEST_F(LedControllerTest, LdInstructionShouldNotPrintLedState)
{
  controller.runProgram(Instructions{createInstructionWithZeroValue(InstructionType::LdA)});

  EXPECT_THAT(stream.str(), Eq(""));
}

TEST_F(LedControllerTest, ShouldAcceptNoInstructions)
{
  controller.runProgram(Instructions{});

  EXPECT_THAT(stream.str(), Eq(""));
}