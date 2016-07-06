#pragma once

#include <random>
#include <algorithm>
#include <vector>
#include <functional>
#include <ostream>

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
    case Move::rock:
        return out << "rock";
    case Move::paper:
        return out << "paper";
    case Move::scissors:
        return out << "scissors";
    }
}

class NextMove
{
public:
    NextMove()
        : device{},
          generator{device()},
          distribution{0, 2}
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
        return (rhsMove == Move::rock) ? MatchResult::tie : ((rhsMove == Move::paper) ? MatchResult::rhsWins : MatchResult::lhsWins);
    case Move::paper:
        return (rhsMove == Move::paper) ? MatchResult::tie : ((rhsMove == Move::scissors) ? MatchResult::rhsWins : MatchResult::lhsWins);
    case Move::scissors:
        return (rhsMove == Move::scissors) ? MatchResult::tie : ((rhsMove == Move::rock) ? MatchResult::rhsWins : MatchResult::lhsWins);
    }
}

}
