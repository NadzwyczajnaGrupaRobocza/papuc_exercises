#pragma once
#include <chrono>
#include <iomanip>
#include <iosfwd>
#include <iostream>
#include <string>

namespace util
{
using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::high_resolution_clock::time_point;

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

class Log
{
public:
    virtual ~Log() = default;

    virtual LogLine info() = 0;
    virtual LogLine error() = 0;
    virtual LogLine debug() = 0;
};
}
