#include <cstdlib>
#include <ctime>
#include <iostream>

#include "MB_04_10.hpp"

std::ostream& operator<<(std::ostream& out, Gesture gesture)
{
    switch (gesture)
    {
    case Gesture::Paper: out << "Paper"; break;
    case Gesture::Scissors: out << "Scissors"; break;
    case Gesture::Rock: out << "Rock"; break;
    default: out << "Error"; break;
    }
    return out;
}

std::istream& operator>>(std::istream& in, Gesture& gesture)
{
    unsigned uintIn;
    in >> uintIn;
    switch (uintIn)
    {
    case static_cast<int>(Gesture::Paper): gesture = Gesture::Paper; break;
    case static_cast<int>(Gesture::Scissors):
        gesture = Gesture::Scissors;
        break;
    case static_cast<int>(Gesture::Rock): gesture = Gesture::Rock; break;
    default: gesture = Gesture::Error; break;
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, Result result)
{
    switch (result)
    {
    case Result::Defeat: out << "You loose"; break;
    case Result::Draw: out << "Draw"; break;
    case Result::Win: out << "You win"; break;
    default: out << "Error..."; break;
    }
    return out;
}

Gesture uint2Gesture(unsigned source)
{
    Gesture output = Gesture::Error;
    switch (source)
    {
    case static_cast<int>(Gesture::Paper): output = Gesture::Paper; break;
    case static_cast<int>(Gesture::Scissors): output = Gesture::Scissors; break;
    case static_cast<int>(Gesture::Rock): output = Gesture::Rock; break;
    default: output = Gesture::Error; break;
    }
    return output;
}

Gesture Player::getGesture() const
{
    this->showOptions();

    Gesture selection = Gesture::Error;
    std::cin >> selection;
    while (selection == Gesture::Error)
    {
        std::cout << "Your selection is not on list, try again." << std::endl;
        showOptions();
        std::cin >> selection;
    }

    return selection;
}

void Player::showOptions() const
{
    std::cout << "1. Paper" << std::endl
              << "2. Scissors" << std::endl
              << "3. Rock" << std::endl;
    std::cout << "Select Your gesture: ";
}

Gesture Opponent::getGesture() const
{
    srand(time(NULL));
    unsigned randomNumber = (rand() % 3) + 1;
    Gesture selection = uint2Gesture(randomNumber);
    return selection;
}

void Game::playOneRound(const Player& player, const Opponent& opponent)
{
    Gesture oSelection = opponent.getGesture();
    Gesture pSelection = player.getGesture();
    std::cout << "Your selection: " << pSelection << std::endl;
    std::cout << "Opponent selection: " << oSelection << std::endl;

    Result result = getResult(oSelection, pSelection);

    std::cout << "Result of game: " << result << std::endl;
}

Result Game::getResult(Gesture oGesture, Gesture pGesture)
{
    Result result = Result::Draw;

    if (oGesture == pGesture)
    {
        result = Result::Draw;
    }
    else if ((oGesture == Gesture::Paper && pGesture == Gesture::Scissors) ||
             (oGesture == Gesture::Scissors && pGesture == Gesture::Rock) ||
             (oGesture == Gesture::Rock && pGesture == Gesture::Paper))
    {
        result = Result::Win;
    }
    else
    {
        result = Result::Defeat;
    }
    return result;
}
