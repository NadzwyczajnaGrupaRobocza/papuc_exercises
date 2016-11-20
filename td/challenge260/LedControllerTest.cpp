#include "gmock/gmock.h"

#include <sstream>
#include <bitset>

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
  std::string ledState{getLedStateFromInteger(0)};

  void runInstruction(const Instruction & instruction)
  {
    switch (instruction.type)
    {
      case InstructionType::OutA:
        out << ledState;
        break;
      case InstructionType::LdA:
        ledState = getLedStateFromInteger(instruction.value);
        break;
    }
  }

  static std::string getLedStateFromInteger(unsigned value)
  {
    const std::bitset<8> bitValue{value};
    std::stringstream stream;
    stream << bitValue;
    auto text = stream.str();
    std::transform(text.cbegin(), text.cend(), text.begin(), [](const auto character)
    {
      if (character == '1')
      {
        constexpr auto ledOnChar = '*';
        return ledOnChar;
      }
      else
      {
        constexpr auto ledOffChar = '.';
        return ledOffChar;
      }
    });
    return text + '\n';
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

TEST_F(LedControllerTest, OutInstructionShouldPrintLedStateAfterChangeByLd)
{
  controller.runProgram(Instructions{{InstructionType::LdA, 255}, createInstructionWithZeroValue(InstructionType::OutA)});

  EXPECT_THAT(stream.str(), Eq("********\n"));
}

TEST_F(LedControllerTest, OutInstructionShouldPrintLedStateAfterChangeByLdToSomeValue)
{
  controller.runProgram(Instructions{{InstructionType::LdA, 42}, createInstructionWithZeroValue(InstructionType::OutA)});

  EXPECT_THAT(stream.str(), Eq("..*.*.*.\n"));
}