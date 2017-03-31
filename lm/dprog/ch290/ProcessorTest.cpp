#include "Processor.hpp"
#include "gtest/gtest.h"

namespace ltm
{
TEST(ProcessorTest, willProcessTwoInstructions)
{
    const auto expected_value = u8_t{129};
    Processor::Program testProgram = {
        Instruction{OperationType::load, Register::reg_a, expected_value,
                    Register::INVALID},
        Instruction{OperationType::output, Register::out_0, u8_t{0},
                    Register::reg_a}};

    u8_t output = 0;
    auto output_listener = [&](const u8_t v) { output = v; };

    Processor p{{{Register::out_0, output_listener}}};

    p.runProgram(testProgram);
    ASSERT_EQ(output, expected_value);
}

TEST(ProcessorTest, willRotateRegisterLeftWithoutCarry)
{
    const auto initial_value = u8_t{1};
    const auto expected_output = std::vector<u8_t>{static_cast<u8_t>(2)};
    Processor::Program testProgram = {
        Instruction{OperationType::load, Register::reg_a, initial_value,
                    Register::INVALID},
        Instruction{OperationType::rotateLeftCyclic, Register::reg_a,
                    u8_t{0}, Register::INVALID},
        Instruction{OperationType::output, Register::out_0, u8_t{0},
                    Register::reg_a}};

    std::vector<u8_t> output{};
    auto output_listener = [&](const u8_t v) { output.push_back(v); };

    Processor p{{{Register::out_0, output_listener}}};

    p.runProgram(testProgram);
    ASSERT_EQ(output.size(), 1u);
    ASSERT_EQ(output, expected_output);
}

TEST(ProcessorTest, willRotateRegisterLeftWithCarry)
{
    const auto initial_value = u8_t{128 + 32};
    const auto expected_output = std::vector<u8_t>{static_cast<u8_t>(1 + 64)};
    Processor::Program testProgram = {
        Instruction{OperationType::load, Register::reg_a, initial_value,
                    Register::INVALID},
        Instruction{OperationType::rotateLeftCyclic, Register::reg_a,
                    u8_t{0}, Register::INVALID},
        Instruction{OperationType::output, Register::out_0, u8_t{0},
                    Register::reg_a}};

    std::vector<u8_t> output{};
    auto output_listener = [&](const u8_t v) { output.push_back(v); };

    Processor p{{{Register::out_0, output_listener}}};

    p.runProgram(testProgram);
    ASSERT_EQ(output.size(), 1u);
    ASSERT_EQ(output, expected_output);
}

TEST(ProcessorTest, willRotateRegisterRightWithoutCarry)
{
    const auto initial_value = u8_t{2};
    const auto expected_output = std::vector<u8_t>{static_cast<u8_t>(1)};
    Processor::Program testProgram = {
        Instruction{OperationType::load, Register::reg_a, initial_value,
                    Register::INVALID},
        Instruction{OperationType::rotateRightCyclic, Register::reg_a,
                    u8_t{0}, Register::INVALID},
        Instruction{OperationType::output, Register::out_0, u8_t{0},
                    Register::reg_a}};

    std::vector<u8_t> output{};
    auto output_listener = [&](const u8_t v) { output.push_back(v); };

    Processor p{{{Register::out_0, output_listener}}};

    p.runProgram(testProgram);
    ASSERT_EQ(output.size(), 1u);
    ASSERT_EQ(output, expected_output);
}

TEST(ProcessorTest, willRotateRegisterRightWithCarry)
{
    const auto initial_value = u8_t{16 + 1};
    const auto expected_output = std::vector<u8_t>{static_cast<u8_t>(8 + 128)};
    Processor::Program testProgram = {
        Instruction{OperationType::load, Register::reg_a, initial_value,
                    Register::INVALID},
        Instruction{OperationType::rotateRightCyclic, Register::reg_a,
                    u8_t{0}, Register::INVALID},
        Instruction{OperationType::output, Register::out_0, u8_t{0},
                    Register::reg_a}};

    std::vector<u8_t> output{};
    auto output_listener = [&](const u8_t v) { output.push_back(v); };

    Processor p{{{Register::out_0, output_listener}}};

    p.runProgram(testProgram);
    ASSERT_EQ(output.size(), 1u);
    ASSERT_EQ(output, expected_output);
}

TEST(ProcessorTest, willLoop)
{
    const auto initial_value = u8_t{16};
    const auto loop_count = u8_t{3};
    const auto expected_output = [=] {
        std::vector<u8_t> tmp;
        for (int i = 0; i < loop_count; ++i)
            tmp.push_back(initial_value);

        return tmp;
    }();

    Processor::Program testProgram = {
        Instruction{OperationType::load, Register::reg_a, initial_value,
                    Register::INVALID},
        Instruction{OperationType::load, Register::reg_b, loop_count,
                    Register::INVALID},
        Instruction{OperationType::output, Register::out_0, u8_t{0},
                    Register::reg_a},
        Instruction{OperationType::decrementAndJump, Register::reg_b,
                    u8_t{2}, Register::reg_a}};

    std::vector<u8_t> output{};
    auto output_listener = [&](const u8_t v) { output.push_back(v); };

    Processor p{{{Register::out_0, output_listener}}};

    p.runProgram(testProgram);
    ASSERT_EQ(output.size(), 3u);
    ASSERT_EQ(output, expected_output);
}
}
