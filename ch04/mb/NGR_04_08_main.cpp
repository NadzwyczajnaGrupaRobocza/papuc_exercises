#include "NGR_04_08_01.hpp"
#include <iostream>
#include <stdexcept>

int main()
{
	std::cout << "Podaj liczbę ziarenek ryżu: " << std::endl;
	
	long long riceGrains;
	std::cin >> riceGrains;
	
	RiceFromChessboard riceCalculator = RiceFromChessboard();
	try
	{
		auto squares = riceCalculator.getNumberOfSquares(riceGrains);
		std::cout << "Aby otrzymać " << riceGrains << " ziarenek ryżu należy zapełnić "
		          << squares << " pól szachownicy." << std::endl;
	}
    catch(const std::runtime_error& error)
    {
        std::cerr << "Error: " << error.what() << std::endl;
        return 1;
    }
	
    return 0;
}
