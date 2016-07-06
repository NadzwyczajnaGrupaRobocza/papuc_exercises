#include <iostream>
#include <string>
#include <vector>

#include "RPS.hpp"

int main()
{
    std::cout << "The mighty random number generator is upon you.\n"
                 "To survive the encounter with such monstrosity you need to\n"
                 "beat the beast in an ultimate test of wit...\n"
                 "You'll need a rock, paper... and scissors, of course.\n"
                 "Input your move as a single letter \"r\", \"p\" or \"s\".\n"
                 "Typing in \"q\" ends the duel.\n"
                 "Time to make your move!\n";

    using SizeType = std::vector<RPS::Move>::size_type;
    constexpr SizeType maxGameLength = 10u;
    std::vector<RPS::Move> userMoves{maxGameLength};
    std::vector<RPS::Move> rngMoves = RPS::createGameVector(maxGameLength);
    SizeType currentMove{0};
    bool isRunning = true;
    while (isRunning)
    {
        std::string input;
        std::cin >> input;

        if (input.length() == 0)
        {
            continue;
        }

        switch (input[0])
        {
        case 'r': userMoves[currentMove] = RPS::Move::rock; break;
        case 'p': userMoves[currentMove] = RPS::Move::paper; break;
        case 's': userMoves[currentMove] = RPS::Move::scissors; break;
        case 'q': isRunning = false; continue;
        default: continue;
        }

        std::cout << "You play: " << userMoves[currentMove]
                  << ", beast plays: " << rngMoves[currentMove] << ". ";
        switch (
            RPS::getMatchResult(userMoves[currentMove], rngMoves[currentMove]))
        {
        case RPS::MatchResult::tie:
            std::cout << "There is a stalemate between you and the beast. "
                         "Fight on, noble warrior.\n";
            break;
        case RPS::MatchResult::lhsWins:
            std::cout << "You have won this skirmish, noble knight!\n";
            break;
        case RPS::MatchResult::rhsWins:
            std::cout
                << "The beast won this time, but there may still be hope...\n";
            break;
        }

        ++currentMove;
        if (currentMove >= maxGameLength)
        {
            isRunning = false;
        }
    }

    auto tournamentResult = getTournamentResult(userMoves, rngMoves);

    switch (tournamentResult)
    {
    case RPS::MatchResult::tie:
        std::cout << "You failed to slay the beast, noble knight."
                     "The beast failed to harm you as well. You both live to "
                     "fight another day.\n";
        break;
    case RPS::MatchResult::lhsWins:
        std::cout << "You slayed the beast, noble knight."
                  << " "
                  << "Fame and ethernal glory await you.\n";
        break;
    case RPS::MatchResult::rhsWins:
        std::cout << "The beast slaughered you, noble knight."
                  << " "
                  << "May your bravery and sacrifice by an inspiration"
                  << " to the next champion.\n";
        break;
    default:
        std::cout << "ERROR!!!";
    }

    return 0;
}
