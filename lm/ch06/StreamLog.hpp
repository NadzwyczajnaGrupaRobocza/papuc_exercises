#include "Log.hpp"
#include <iostream>
#include <string>

namespace util
{

class StreamLog : public Log
{
public:
    StreamLog(std::ostream& outInit)
        : out{outInit}
    {
        ourEpoch = Clock::now();
    }

    LogLine info() override
    {
        return LogLine{out, ourEpoch, "INF "};
    }

    LogLine error() override
    {
        return LogLine{out, ourEpoch, "ERR "};
    }

    LogLine debug() override
    {
        return LogLine{out, ourEpoch, "DBG "};
    }
private:

    std::ostream& out;
    TimePoint ourEpoch;
};


}
