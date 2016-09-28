#include <cmath>
#include <string>
#include <stdexcept>

#include "Common.hpp"

namespace mbcommon
{

bool doublesAreEqual(const double& first, const double& second,
                     const double& epsilon)
{
    if (std::fabs(first - second) < epsilon)
    {
        return true;
    }
    else
    {
        return false;
    }
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

void error(std::string cause)
{
    std::logic_error logicError(cause);
    throw logicError;
}

} // namespace mbcommon
