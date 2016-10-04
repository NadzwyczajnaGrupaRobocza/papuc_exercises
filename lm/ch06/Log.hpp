#pragma once
#include <iosfwd>

namespace util
{

class Log
{
public:
    virtual ~Log() = default;

    virtual std::ostream& info() = 0;
    virtual std::ostream& error() = 0;
    virtual std::ostream& debug() = 0;
};

}
