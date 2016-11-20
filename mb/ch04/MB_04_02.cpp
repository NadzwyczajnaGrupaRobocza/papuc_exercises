#include "MB_04_02.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>

std::vector<double> collectTemperatures()
{
    std::vector<double> dataContainer;
    double singleData;
    std::cout << "Podaj temperaturę: ";
    while (std::cin >> singleData)
    {
        dataContainer.push_back(singleData);
        std::cout << "Podaj temperaturę: ";
    }

    return dataContainer;
}

std::string showVector(const std::vector<double>& vect)
{
    std::stringstream stringedVector;
    stringedVector << "[";
    for (unsigned i = 0; i < vect.size(); ++i)
    {
        stringedVector << vect[i];
        if (i != vect.size() - 1)
        {
            stringedVector << ", ";
        }
    }
    stringedVector << "]";

    return stringedVector.str();
}

double getMedian(const std::vector<double>& data)
{
    std::vector<double> temp(data);
    std::sort(temp.begin(), temp.end());
    auto numberOfData = temp.size();
    auto middleIndex = temp.size() / 2;
    double mediana = 0.0;

    if (numberOfData % 2 == 1)
    {
        mediana = temp[middleIndex];
    }
    else
    {
        mediana = (temp[middleIndex - 1] / 2) + (temp[middleIndex] / 2);
    }

    return mediana;
}
