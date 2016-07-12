#include "SquareEquation.h"

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <algorithm>

Polynomial::Polynomial(std::vector<double> pol)
{	
	auto nonZero = std::find_if( pol.rbegin(), pol.rend(), [](double val){ return val != 0;});
	std::copy( pol.begin(), nonZero.base(), std::back_inserter( polynom));
}

Polynomial::Polynomial()
{
	polynom.push_back(0);
}

int Polynomial::getDegree() const
{
	return polynom.size() -1;
}


SquareEquation::SquareEquation(const Polynomial &sqr)
{
	square = sqr;
}



double SquareEquation::delta()
{
	return square[1]*square[1]-4.*square[2]*square[0];
}

bool SquareEquation::isSquare()
{
	if(square[2] != 0)
	{
		return true;	
	}
	else
	{
		return false;
	}
}

std::vector<double> SquareEquation::solveEquation()
{
	std::vector<double> result; 
	double D = delta();	
	if(isSquare())
	{
		if(D >= 0)
		{
			result.push_back((-square[1] + std::sqrt(D))/(2.*square[2]));
			result.push_back((-square[1] - std::sqrt(D))/(2.*square[2]));				
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
