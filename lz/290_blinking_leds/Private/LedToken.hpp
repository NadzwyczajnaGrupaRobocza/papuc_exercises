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
    LedToken(const LedToken&);
    LedToken(LedToken&&);

    friend std::ostream& operator<<(std::ostream&, const LedToken&);
    friend bool operator==(const LedToken&, const LedToken&);

    const std::string& str() const &;
    std::string str() const &&;

    template <class F, class S>
    std::pair<F, S> split(const Delimiter&) const;

private:
    const std::string value;
};
}
