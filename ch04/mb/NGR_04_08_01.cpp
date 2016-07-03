#include "NGR_04_08_01.hpp"
#include <iostream>
#include <cmath>

int RiceFromChessboard::getNumberOfSquares(long long riceGrains)
{
	if(riceGrains < 0)
	{
		std::string error = "Number of grains should be positive!";
		throw error;
	}
	
	int currentSquare = 0;
	long long numberOfGrainsOnCurrentSquare = 0;
	long long numberOfGrainsFromAllSquares = 0;

	while(numberOfGrainsFromAllSquares < riceGrains)
	{
		++currentSquare;
		numberOfGrainsOnCurrentSquare = std::pow(2, currentSquare);
		numberOfGrainsFromAllSquares += numberOfGrainsOnCurrentSquare;
	}
	
	return currentSquare;
}
