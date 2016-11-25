#include "MB_04_08.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>

int RiceFromChessboard::getNumberOfSquares(long long riceGrains)
{
    if (riceGrains < 0)
    {
        std::out_of_range error("Number of rice grains shouldn't be negative");
        throw error;
    }

    int currentSquare = 0;
    long long numberOfGrainsOnCurrentSquare = 0;
    long long numberOfGrainsFromAllSquares = 0;

    while (numberOfGrainsFromAllSquares < riceGrains)
    {
        ++currentSquare;
        numberOfGrainsOnCurrentSquare = static_cast<long long>(std::pow(2, currentSquare));
        numberOfGrainsFromAllSquares += numberOfGrainsOnCurrentSquare;
    }

    return currentSquare;
}
