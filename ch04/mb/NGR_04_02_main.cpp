#include <iostream>
#include <vector>
#include <algorithm>
#include "NGR_04_02_01.hpp"

int main()
{
    std::cout << "=== Program liczący medianę ===" << std::endl;
    std::cout << "= wpisanie wartości innej niż double kończy zbieranie danych" << std::endl;
    std::vector<double> temperatures;

    temperatures = collectData();
    std::sort(temperatures.begin(), temperatures.end());
    showMediana(temperatures);

    return 0;
}
