#include <iostream>
#include <vector>
#include "NGR_04_02_01.hpp"

std::vector<double> collectData()
{
    std::vector<double> dataContainer;
    double singleData;
    std::cout << "Podaj temperaturę: ";
    while(std::cin >> singleData)
    {
        dataContainer.push_back(singleData);
        std::cout << "Podaj temperaturę: ";
    }

    return dataContainer;
}

std::string showVector(const std::vector<double>& vect)
{
    std::string stringedVector = "[";
    for(unsigned i=0; i<vect.size(); ++i)
    {
        stringedVector += vect[i];
        if(i!=vect.size()-1)
        {
            stringedVector +=  ", ";
        }
    }
    stringedVector +=  "]";
    
    return stringedVector;	
}

void showMediana(const std::vector<double>& data)
{
    int numberOfData = data.size();
    int middleIndex = data.size() / 2;

    if(numberOfData == 0)
    {
        std::cout << "Brak danych => Brak mediany" << std::endl;
    }
    else if(numberOfData % 2 == 1)
    {
        std::cout << "Mediana : " << data[middleIndex] << std::endl;
    }
    else
    {
        std::cout << "Mediana : " << (data[middleIndex - 1] / 2) + (data[middleIndex] / 2) << std::endl;
    }
}
