#include "RPS.hpp"
#include "gtest/gtest.h"

TEST(LMCh04Ex10, willReturnRandomVectorOfProperSize)
{
    constexpr auto expected_size = std::vector<RPS::Move>::size_type(11);
    auto game = RPS::createGameVector(expected_size);

    ASSERT_EQ(game.size(), expected_size);
    ASSERT_TRUE(std::all_of(game.begin(), game.end(), [](const RPS::Move m) {
        return m == RPS::Move::rock or m == RPS::Move::paper or
               m == RPS::Move::scissors;
    }));
}

TEST(LMCh04Ex10, willReturnProperTournamentResult_rhsWins)
{
    std::vector<RPS::Move> lhsMoves;
    std::fill_n(std::back_inserter(lhsMoves), 5, RPS::Move::rock);

    std::vector<RPS::Move> rhsMoves;
    std::fill_n(std::back_inserter(rhsMoves), 5, RPS::Move::paper);

    ASSERT_EQ(RPS::MatchResult::rhsWins,
              RPS::getTournamentResult(lhsMoves, rhsMoves));
}

TEST(LMCh04Ex10, willReturnProperTournamentResult_lhsWins)
{
    std::vector<RPS::Move> lhsMoves;
    std::fill_n(std::back_inserter(lhsMoves), 4, RPS::Move::rock);

    std::vector<RPS::Move> rhsMoves;
    std::fill_n(std::back_inserter(rhsMoves), 2, RPS::Move::scissors);

    ASSERT_EQ(RPS::MatchResult::lhsWins,
              RPS::getTournamentResult(lhsMoves, rhsMoves));
}
