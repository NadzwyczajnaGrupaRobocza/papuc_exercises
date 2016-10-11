#include <cmath>
#include <string>
#include <stdexcept>

#include "Common.hpp"

namespace mbcommon
{

bool doublesAreEqual(const double& first, const double& second,
                     const double& epsilon)
{
    return std::fabs(first - second) < epsilon;
}

int factorial(const unsigned& value)
{
    if(value == 0 or value == 1)
    {
        return 1;
    }
    else
    {
        return value * factorial(value -1);
    }
}

} // namespace mbcommon
