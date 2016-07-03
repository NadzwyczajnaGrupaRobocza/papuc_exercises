#include "NGR_04_08_01.hpp"
#include <iostream>

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
	catch(std::string error)
    {
        std::cerr << "Error: " << error << "\n";
        return 1;
    }
	
    return 0;
}
