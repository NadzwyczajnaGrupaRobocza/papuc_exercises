#include <cmath>

#include "MB_Common.hpp"

namespace mbcommon
{

bool doublesAreEqual(const double& first, const double& second, const double& epsilon)
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


} //namespace mbcommon
