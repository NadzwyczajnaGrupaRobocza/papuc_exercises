#include "Log.hpp"

namespace util
{
class StreamLog : public Log
{
public:
    StreamLog(std::ostream& outInit)
        : out{outInit}
    {
    }

    std::ostream& info() override
    {
        return out << "INF ";
    }

    std::ostream& error() override
    {
        return out << "ERR ";
    }

    std::ostream& debug() override
    {
        return out << "DBG ";
    }
private:
    std::ostream& out;
};
}
