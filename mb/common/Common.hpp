#pragma once

#include <string>

namespace mbcommon
{

bool doublesAreEqual(const double&, const double&,
                     const double& epsilon = 0.00000001);

int factorial(const unsigned&);
} // namespace mbcommon
