#pragma once

#include <random>
#include <algorithm>
#include <vector>

namespace RPS
{
enum class Move
{
    rock,
    paper,
    scissors
};

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
    std::generate(game.begin(), game.end(), [&]()
                  {
                      return nm();
                  });
    return game;
}

}
