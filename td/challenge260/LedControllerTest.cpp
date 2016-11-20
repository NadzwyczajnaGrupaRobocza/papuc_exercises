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

  void runProgram(const Instructions &)
  {
    out << "........\n";
  }

private:
  std::ostream &out;

};

static constexpr Instruction createInstructionWithZeroValue(InstructionType type)
{
  return{type, 0};
}

using namespace ::testing;

TEST(LedControllerTest, OutInstructionShouldPrintLedState)
{
  std::stringstream stream;
  LedController controller{stream};

  controller.runProgram(Instructions{createInstructionWithZeroValue(InstructionType::OutA)});

  EXPECT_THAT(stream.str(), Eq("........\n"));
}