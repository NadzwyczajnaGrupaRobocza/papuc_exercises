#pragma once

enum class Gesture
{
    Error = 0,
    Paper = 1,
    Scissors = 2,
    Rock = 3
};

enum class Result : int
{
    Defeat = -1,
    Draw = 0,
    Win = 1
};

std::ostream& operator<<(std::ostream& out, Gesture e);
std::istream& operator>>(std::istream& in, Gesture& e);

std::ostream& operator<<(std::ostream& out, Result e);

Gesture uint2Gesture(unsigned);

class Player
{
public:
    Gesture getGesture() const;

private:
    void showOptions() const;
};

class Opponent
{
public:
    Gesture getGesture() const;
};

class Game
{
public:
    void playOneRound(const Player&, const Opponent&);

private:
    Result getResult(Gesture, Gesture);
};
