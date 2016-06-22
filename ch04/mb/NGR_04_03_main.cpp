#include <iostream>
#include <vector>
#include <algorithm>
#include "NGR_04_03_01.hpp"

int main()
{
    std::cout << "=== Exercise 03 from Chapter 04 ===" << std::endl;

    std::vector<double> distances = collectData();

    std::cout << "Total distance: " << getTotalDistance(distances) << std::endl;
    std::cout << "Smallest distance: " << getSmallestDistance(distances) << std::endl;
    std::cout << "Largest distance: " << getLargestDistance(distances) << std::endl;
    std::cout << "Mean distance: " << getMeanDistance(distances) << std::endl;

    return 0;
}
