#include <iostream>
#include <vector>
#include "NGR_04_02_01.hpp"

int main()
{
    std::cout << "=== Program liczący medianę ===" << std::endl;
    std::cout << "= wpisanie wartości innej niż double kończy zbieranie danych" << std::endl;
    std::vector<double> temperatures;

    temperatures = collectData();
    if(temperatures.size() == 0)
    {
        std::cout << "Brak danych => Brak mediany" << std::endl;
        return 1;
    }

    std::cout << "Mediana : " << getMediana(temperatures) << std::endl;

    return 0;
}
