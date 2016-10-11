#include "ExpressionSplitter.hpp"

#include <sstream>

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// trim from both ends (copying)
static inline std::string trimmed(std::string s) {
    trim(s);
    return s;
}

namespace calc
{
std::vector<std::string> ExpressionSplitter::split(const std::string& in)
{
    std::string inLocal = in;
    trim(inLocal);
    if (inLocal.length() == 0) return {};

    unsigned long num_sep = std::count(in.begin(), in.end(), ';');
    std::stringstream ss{in};

    std::vector<std::string> rv;
    std::string expr;

    while (std::getline(ss, expr, ';'))
    {
        rv.push_back(expr);
    }

    appendPreviousIncompleteInput(rv);

    if (num_sep != rv.size())
    {
        if (num_sep + 1 == rv.size())
        {
            handleIncompleteInput(rv);
        }
        else
        {
            throw std::runtime_error("execute order 66");
        }
    }

    std::transform(rv.begin(), rv.end(), rv.begin(),
                   [](const auto &s)
                   {
                       return trimmed(s);
                   });

    return rv;
}

void ExpressionSplitter::appendPreviousIncompleteInput(std::vector<std::string>& inputVec)
{
    inputVec[0] = lastLineLeftover + " " + inputVec[0];
    lastLineLeftover = "";
}
void ExpressionSplitter::handleIncompleteInput(std::vector<std::string>& incomplete)
{
    lastLineLeftover = incomplete.back();
    incomplete.pop_back();
}

bool ExpressionSplitter::hasIncompleteInput()
{
    return lastLineLeftover.length() > 0;
}
}
