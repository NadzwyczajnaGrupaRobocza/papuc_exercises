#pragma once
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

namespace common
{
using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::high_resolution_clock::time_point;
namespace detail
{
class LogLine
{
public:
    LogLine(std::ostream& outInit, const TimePoint& ourEpoch,
            const std::string& prefix)
        : out{outInit}
    {
        auto now = Clock::now();
        out << std::setw(10) << std::setfill('0')
            << std::chrono::nanoseconds(now - ourEpoch).count() << ' '
            << prefix;
    }

    ~LogLine()
    {
        out << std::endl;
    }

    std::ostream& stream()
    {
        return out;
    }

    template <typename T>
    LogLine& operator<<(T input)
    {
        out << input;
        return *this;
    }

private:
    std::ostream& out;
};
}

class Log
{
public:
    virtual ~Log() = default;

    virtual detail::LogLine info() = 0;
    virtual detail::LogLine error() = 0;
    virtual detail::LogLine debug() = 0;
};
}
