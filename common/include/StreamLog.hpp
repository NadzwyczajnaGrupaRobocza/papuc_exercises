#include "Log.hpp"
#include <iostream>
#include <string>

namespace common
{

class StreamLog : public Log
{
public:
    StreamLog(std::ostream& outInit)
        : out{outInit}
    {
        ourEpoch = Clock::now();
    }

    detail::LogLine info() override
    {
        return detail::LogLine{out, ourEpoch, "INF "};
    }

    detail::LogLine error() override
    {
        return detail::LogLine{out, ourEpoch, "ERR "};
    }

    detail::LogLine debug() override
    {
        return detail::LogLine{out, ourEpoch, "DBG "};
    }
private:

    std::ostream& out;
    TimePoint ourEpoch;
};


}
