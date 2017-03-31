#pragma once
#include <iosfwd>
#include <string>
#include <utility>

namespace lz
{
class LedToken
{
public:
    using Delimiter = char;

    LedToken(std::string);

    friend std::ostream& operator<<(std::ostream&, const LedToken&);
    friend bool operator==(const LedToken&, const LedToken&);

    const std::string& str() const &;
    std::string str() const &&;

    template <class F, class S>
    std::pair<F, S> split(const Delimiter&) const;

private:
    std::string value;
};


template <>
std::pair<std::string, std::string> LedToken::split(const Delimiter&) const;

template <>
std::pair<std::string, int> LedToken::split(const Delimiter&) const;

}
