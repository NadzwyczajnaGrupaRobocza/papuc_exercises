#include "Grains.hpp"

largeNum squaresForGrains(largeNum grains)
{
    largeNum squareCt = 1;
    largeNum grainsFit = 1;
    largeNum currPow = 1;
    while (grainsFit < grains)
    {
        currPow *= 2;
        grainsFit += currPow;
        squareCt++;
    }

    return squareCt;
}
