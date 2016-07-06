#include "SquareEquation.h"

#include <iostream>
#include <stdexcept>
#include <cmath>

SquareEquation::SquareEquation():a(1), b(0), c(0)
{
}

SquareEquation::SquareEquation(float aA, float bB, float cC):a(aA), b(bB), c(cC)
{
}

void SquareEquation::setEquationEntries(float aA, float bB, float cC)
{
	a = aA;
	b = bB;
	c = cC;
}

float SquareEquation::delta()
{
	return b*b-4.*a*c;
}

bool SquareEquation::isSquare()
{
	if(a != 0)
	{
		return true;	
	}
	else
	{
		return false;
	}
}

std::vector<float> SquareEquation::solveEquation()
{
	std::vector<float> result; 
	float D =delta();	
	if(isSquare())
	{
		if(D >= 0)
		{
			result.push_back((-b + std::sqrt(D))/(2.*a));
			result.push_back((-b - std::sqrt(D))/(2.*a));				
			return result;		
		}
		else
		{
			throw std::runtime_error("Negative discriminant");
		}

	}
	else
	{
		throw std::runtime_error("This is not square equation");
	}
}
