#include <gtest/gtest.h>
#include <iostream>
#include <sstream>

#include "BlinkingLeds.hpp"

namespace lz
{
class BlinkingLedsTest : public ::testing::Test
{
public:
    void SetUp() override
    {
        cin_buffer = std::cin.rdbuf(input.rdbuf());
        cout_buffer = std::cout.rdbuf(output.rdbuf());
    }

    void TearDown() override
    {
        std::cout.rdbuf(cout_buffer);
        std::cin.rdbuf(cin_buffer);
    }

    std::istringstream input{};
    std::ostringstream output{};

private:
    decltype(std::cout.rdbuf()) cout_buffer;
    decltype(std::cin.rdbuf()) cin_buffer;
};
TEST_F(BlinkingLedsTest, part_one)
{
    input = std::istringstream{"out (0),a\n"
                               "ld a,12\n"
                               "ld a,6\n"
                               "out (0),a\n"
                               "out (0),a\n"
                               "ld a,77\n"
                               "out (0),a\n"
                               "ld a,255\n"
                               "out (0),a\n"};

    lz::BlinkingLeds::run();

    EXPECT_EQ("........\n"
              ".....**.\n"
              ".....**.\n"
              ".*..**.*\n"
              "********\n",
              output.str());
}
}
