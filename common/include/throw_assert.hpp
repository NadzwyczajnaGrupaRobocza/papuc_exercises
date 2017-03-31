#pragma once

#include <exception>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <gsl/gsl_assert>

namespace common
{
namespace detail
{
/// Exception type for assertion failures
class AssertionFailureException : public std::exception
{
private:
    const char* expression;
    const char* file;
    int line;
    std::string message;
    std::string report;

public:
    /// Helper class for formatting assertion message
    class StreamFormatter
    {
    private:
        std::ostringstream stream;

    public:
        operator std::string() const
        {
            return stream.str();
        }

        template <typename T>
        StreamFormatter& operator<<(const T& value)
        {
            stream << value;
            return *this;
        }
    };

    /// Log error before throwing
    void LogError()
    {
#ifdef THROWASSERT_LOGGER
        THROWASSERT_LOGGER(report);
#else
        std::cerr << report << std::endl;
#endif
    }

    /// Construct an assertion failure exception
    AssertionFailureException(const char* p_expression, const char* p_file,
                              int p_line, const std::string& p_message)
        : expression(p_expression), file(p_file), line(p_line),
          message(p_message)
    {
        std::ostringstream outputStream;

        if (!message.empty())
        {
            outputStream << message << ": ";
        }

        std::string expressionString = expression;

        if (expressionString == "false" || expressionString == "0" ||
            expressionString == "FALSE")
        {
            outputStream << "Unreachable code assertion";
        }
        else
        {
            outputStream << "Assertion '" << expression << "'";
        }

        outputStream << " failed in file '" << file << "' line " << line;
        report = outputStream.str();

        LogError();
    }

    /// The assertion message
    virtual const char* what() const throw()
    {
        return report.c_str();
    }

    /// The expression which was asserted to be true
    const char* Expression() const throw()
    {
        return expression;
    }

    /// Source file
    const char* File() const throw()
    {
        return file;
    }

    /// Source line
    int Line() const throw()
    {
        return line;
    }

    /// Description of failure
    const char* Message() const throw()
    {
        return message.c_str();
    }

    ~AssertionFailureException() throw()
    {
    }
};
}
}
/// Assert that EXPRESSION evaluates to true, otherwise raise
/// AssertionFailureException with associated MESSAGE (which may use C++
/// stream-style message formatting)
#define throw_assert(EXPRESSION, MESSAGE)                                      \
    do                                                                         \
    {                                                                          \
        if (GSL_UNLIKELY(!(EXPRESSION)))                                       \
        {                                                                      \
            throw common::detail::AssertionFailureException(                   \
                #EXPRESSION, __FILE__, __LINE__,                               \
                (common::detail::AssertionFailureException::StreamFormatter()  \
                 << MESSAGE));                                                 \
        }                                                                      \
    } while (false)
