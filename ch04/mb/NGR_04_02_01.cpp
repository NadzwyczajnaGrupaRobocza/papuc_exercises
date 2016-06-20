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

double getMediana(const std::vector<double>& data)
{
    int numberOfData = data.size();
    int middleIndex = data.size() / 2;
    double mediana = 0.0;

    if(numberOfData % 2 == 1)
    {
        mediana = data[middleIndex];
    }
    else
    {
        mediana = (data[middleIndex - 1] / 2) + (data[middleIndex] / 2);
    }
    
    return mediana;
}
