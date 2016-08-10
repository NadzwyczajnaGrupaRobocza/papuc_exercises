#include <cmath>

#include "MB_Common.hpp"

namespace mbcommon
{

<<<<<<< 2ba5851e562b94f23865961ca33e4222a99c0832
bool doublesAreEqual(const double& first, const double& second,
                     const double& epsilon)
=======
bool doublesAreEqual(const double& first, const double& second, const double& epsilon)
>>>>>>> fix in definition and declaration
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

} // namespace mbcommon
