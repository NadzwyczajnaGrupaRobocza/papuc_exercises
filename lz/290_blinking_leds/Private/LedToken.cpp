#include "LedToken.hpp"

#include <gsl/gsl_assert>
#include <ostream>

namespace lz
{
LedToken::LedToken(std::string v) : value{v}
{
}

LedToken::LedToken(const LedToken& token) : value{token.value}
{
}

LedToken::LedToken(LedToken&& token) : value{std::move(token.value)}
{
}

const std::string& LedToken::str() const &
{
    return value;
}

std::string LedToken::str() const &&
{
    return std::move(value);
}

std::ostream& operator<<(std::ostream& os, const LedToken& token)
{
    return os << token.value;
}

bool operator==(const LedToken& lhs, const LedToken& rhs)
{
    return lhs.value == rhs.value;
}

template <>
std::pair<std::string, std::string> LedToken::split(const Delimiter& del) const

{
    Expects(value.size() >= 3);

    const auto first_of_del = value.find_first_of(del);

    Expects(first_of_del != std::string::npos);
    Expects(first_of_del != 0);
    Expects(first_of_del != value.size() - 1);

    const auto& split_point = value.begin() + first_of_del;

    auto left = std::string{value.begin(), split_point};
    auto right = std::string{split_point + 1, value.end()};
    return std::make_pair(left, right);
}

template <>
std::pair<std::string, int> LedToken::split(const Delimiter& del) const

{
    auto splitted = split<std::string, std::string>(del);
    return std::make_pair(splitted.first, std::stoi(splitted.second));
}
}
