#include "RPS.hpp"
#include "gtest/gtest.h"

TEST(LMCh04Ex10, willReturnRandomVectorOfProperSize)
{
    constexpr auto expected_size = std::vector<RPS::Move>::size_type(11);
    auto game = RPS::createGameVector(expected_size);

    ASSERT_EQ(game.size(), expected_size);
    ASSERT_TRUE(std::all_of(game.begin(), game.end(), [](const RPS::Move m)
                            {
                                return m == RPS::Move::rock
                                    or m == RPS::Move::paper
                                    or m == RPS::Move::scissors;
                            }));
}
