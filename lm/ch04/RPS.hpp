#pragma once

#include <algorithm>
#include <boost/range/algorithm.hpp>
#include <functional>
#include <iostream>
#include <map>
#include <ostream>
#include <random>
#include <vector>

namespace RPS
{
enum class Move
{
    rock,
    paper,
    scissors
};

inline std::ostream& operator<<(std::ostream& out, Move m)
{
    switch (m)
    {
    case Move::rock: return out << "rock";
    case Move::paper: return out << "paper";
    case Move::scissors: return out << "scissors";
    default: return out << "ERROR!!!";
    }
}

class NextMove
{
public:
    NextMove() : device{}, generator{device()}, distribution{0, 2}
    {
    }
    Move get()
    {
        return static_cast<Move>(distribution(generator));
    }

    Move operator()()
    {
        return get();
    }

private:
    std::random_device device;
    std::mt19937 generator;
    std::uniform_int_distribution<> distribution;
};

std::vector<Move> createGameVector(std::vector<Move>::size_type size)
{
    std::vector<Move> game{size};
    NextMove nm;
    std::generate(game.begin(), game.end(), std::ref(nm));
    return game;
}

enum class MatchResult
{
    tie,
    lhsWins,
    rhsWins
};

MatchResult getMatchResult(Move lhsMove, Move rhsMove)
{
    switch (lhsMove)
    {
    case Move::rock:
        return (rhsMove == Move::rock)
                   ? MatchResult::tie
                   : ((rhsMove == Move::paper) ? MatchResult::rhsWins
                                               : MatchResult::lhsWins);
    case Move::paper:
        return (rhsMove == Move::paper)
                   ? MatchResult::tie
                   : ((rhsMove == Move::scissors) ? MatchResult::rhsWins
                                                  : MatchResult::lhsWins);
    case Move::scissors:
        return (rhsMove == Move::scissors)
                   ? MatchResult::tie
                   : ((rhsMove == Move::rock) ? MatchResult::rhsWins
                                              : MatchResult::lhsWins);
    default: throw std::logic_error("unknown enum class Move value");
    }
}

MatchResult getTournamentResult(const std::vector<Move>& lhs,
                                const std::vector<Move>& rhs)
{
    std::vector<MatchResult> singleMatchResult{
        std::min(lhs.size(), rhs.size())};

    boost::transform(lhs, rhs, singleMatchResult.begin(), getMatchResult);

    std::map<MatchResult, unsigned> tally;

    boost::for_each(singleMatchResult, [&](const auto& smr) { tally[smr]++; });
    auto maxElementIter =
        boost::max_element(tally, [](const auto& lhs, const auto& rhs) {
            return lhs.second < rhs.second;
        });

    return maxElementIter->first;
}
}
