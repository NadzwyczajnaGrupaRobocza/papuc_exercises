#include <iostream>
#include <vector>
#include "NGR_04_02_01.hpp"

vector<double> collectData()
{
    vector<double> dataContainer;
    double singleData;
    cout << "Podaj temperaturę: ";
    while(cin >> singleData)
    {
        dataContainer.push_back(singleData);
        cout << "Podaj temperaturę: ";
    }

    return dataContainer;
}

std::string showVector(const std::vector<double>& vect)
{
    std::string stringedVector = "[ ";
    for(int i=0; i<vect.size(); ++i)
    {
        stringedVector += vect[i];
        if(i!=vect.size()-1)
        {
            stringedVector +=  ", ";
        }
    }
    stringedVector +=  " ]";
    
    return stringedVector;	
}

void showMediana(const vector<double>& data)
{
    int numberOfData = data.size();
    int middleIndex = data.size() / 2;

    if(numberOfData == 0)
    {
        cout << "Brak danych => Brak mediany" << endl;
    }
    else if(numberOfData % 2 == 1)
    {
        cout << "Mediana : " << data[middleIndex] << endl;
    }
    else
    {
        cout << "Mediana : " << (data[middleIndex - 1] / 2) + (data[middleIndex] / 2) << endl;
    }
}
