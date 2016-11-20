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
    if (instructions.cbegin()->type == InstructionType::OutA)
    {
      out << "........\n";
    }
  }

private:
  std::ostream &out;

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