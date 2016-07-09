#include "MB_04_03.hpp"
#include <algorithm>
#include <iostream>

std::vector<double> collectDistances()
{
    std::vector<double> dataCollection;
    double singleData;
    std::cout << "Input distance: ";
    while (std::cin >> singleData)
    {
        if (singleData > 0)
        {
            dataCollection.push_back(singleData);
        }
        else
        {
            std::cout << "Distance should be a positive value, data refused"
                      << std::endl;
        }
        std::cout << "Input distance: ";
    }
    return dataCollection;
}

double getTotalDistance(const std::vector<double>& distances)
{
    double totalDistance = 0.0;
    for (auto i = 0ul; i < distances.size(); ++i)
    {
        totalDistance += distances[i];
    }
    return totalDistance;
}

double getSmallestDistance(const std::vector<double>& distances)
{
    double smallestDistance = 0.0;
    if (distances.size() != 0)
    {
        smallestDistance = distances[0];
        for (auto i = 1ul; i < distances.size(); ++i)
        {
            if (distances[i] < smallestDistance)
            {
                smallestDistance = distances[i];
            }
        }
    }

    return smallestDistance;
}

double getLargestDistance(const std::vector<double>& distances)
{
    double largestDistance = 0.0;
    if (distances.size() != 0)
    {
        largestDistance = distances[0];
        for (auto i = 1ul; i < distances.size(); ++i)
        {
            if (distances[i] > largestDistance)
            {
                largestDistance = distances[i];
            }
        }
    }

    return largestDistance;
}

double getMeanDistance(const std::vector<double>& distances)
{
    double meanDistance = 0.0;
    if (distances.size() != 0)
    {
        meanDistance = getTotalDistance(distances) / distances.size();
    }
    return meanDistance;
}
