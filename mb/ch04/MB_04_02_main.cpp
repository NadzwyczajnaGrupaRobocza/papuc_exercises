#include "MB_04_02.hpp"
#include <iostream>

int main()
{
    std::cout << "=== Program liczący medianę ===" << std::endl;
    std::cout << "= wpisanie wartości innej niż double kończy zbieranie danych"
              << std::endl;
    std::vector<double> temperatures;

    temperatures = collectTemperatures();
    if (temperatures.size() == 0)
    {
        std::cout << "Brak danych => Brak mediany" << std::endl;
        return 1;
    }

    std::cout << "Mediana : " << getMedian(temperatures) << std::endl;

    return 0;
}
