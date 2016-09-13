#include "Parser_Poly.hpp"

#include <cctype>
#include <iostream>

#ifdef DEBUGLOG
#define TRACE()                                                                \
    do                                                                         \
    {                                                                          \
        std::cout << __FUNCTION__ << "\n";                                     \
    } while (0)
#else
#define TRACE()
#endif

class Parser_Poly::Impl
{
public:
    Impl(const std::string &);
    std::unique_ptr<AST_Poly::Poly> parse();

private:
    enum class Op
    {
        plus,
        minus
    };
    std::unique_ptr<AST_Poly::Poly> parsePoly();
    std::unique_ptr<AST_Poly::Mono> parseMono();
    std::unique_ptr<AST_Poly::Coeff> parseCoeffGroup();
    std::unique_ptr<AST_Poly::CoeffIdx> parseVarPow();
    std::unique_ptr<AST_Poly::Number> testInputForNumber();
    void parseOp();
    bool parsePlusMinus();
    bool parseMult();
    bool parsePow();
    bool parsedAllInput();
    bool testForVariableName();
    bool testInput(char);

    void advanceIfMatch(char);
    void skipWhitespace();

    std::string input;
    std::string::iterator inputIt;
    Op lastOp;
    const std::string varName = "x";
};

Parser_Poly::Parser_Poly(const std::string& inputInit)
    : impl{std::make_unique<Impl>(inputInit)}
{
}

Parser_Poly::~Parser_Poly()
{
}

std::unique_ptr<AST_Poly::Poly> Parser_Poly::parse()
{
    return impl->parse();
}

Parser_Poly::Impl::Impl(const std::string& inputInit)
    : input{inputInit}, inputIt{input.begin()}, lastOp{Op::plus}
{
}

std::unique_ptr<AST_Poly::Poly> Parser_Poly::Impl::parse()
{
    TRACE();
    return parsePoly();
}

std::unique_ptr<AST_Poly::Poly> Parser_Poly::Impl::parsePoly()
{
    TRACE();
    if (parsedAllInput())
    {
        return nullptr;
    }

    auto mono = parseMono();
    if (mono == nullptr)
    {
        return nullptr;
    }

    parseOp();

    return std::make_unique<AST_Poly::Poly>(std::move(mono), parsePoly());
}

std::unique_ptr<AST_Poly::Mono> Parser_Poly::Impl::parseMono()
{
    TRACE();
    auto coeff = parseCoeffGroup();
    if (coeff == nullptr)
    {
        return nullptr;
    }

    auto coeffIdx = parseVarPow();
    if (coeffIdx == nullptr)
    {
        return nullptr;
    }

    return std::make_unique<AST_Poly::Mono>(std::move(coeff),
                                            std::move(coeffIdx));
}

std::unique_ptr<AST_Poly::Coeff> Parser_Poly::Impl::parseCoeffGroup()
{
    TRACE();
    auto number = testInputForNumber();
    if (number == nullptr)
    {
        number = std::make_unique<AST_Poly::Number>(1);
    }
    advanceIfMatch('*');

    if (lastOp == Op::minus)
    {
        number = std::make_unique<AST_Poly::Number>(-1 * number->getValue());
    }

    return std::make_unique<AST_Poly::Coeff>(std::move(number));
}

std::unique_ptr<AST_Poly::CoeffIdx> Parser_Poly::Impl::parseVarPow()
{
    TRACE();
    skipWhitespace();
    auto isVariable = testForVariableName();

    if (isVariable)
    {
        bool hasPowChar = testInput('^');
        if (hasPowChar)
        {
            advanceIfMatch('^');
            auto pow = testInputForNumber();
            if (pow != nullptr)
            {
                return std::make_unique<AST_Poly::CoeffIdx>(std::move(pow));
            }
            else
            {
                return nullptr;
            }
        }
        else
        {
            return std::make_unique<AST_Poly::CoeffIdx>(
                std::make_unique<AST_Poly::Number>(1));
        }
    }
    else
    {
        return std::make_unique<AST_Poly::CoeffIdx>(
            std::make_unique<AST_Poly::Number>(0));
    }
}

void Parser_Poly::Impl::parseOp()
{
    TRACE();
    skipWhitespace();
    if (inputIt == input.end())
    {
        return;
    }

    switch (*inputIt)
    {
    case '+': lastOp = Op::plus; break;
    case '-': lastOp = Op::minus; break;
    default:
        throw std::logic_error(
            "unknown opertor at " +
            std::to_string(std::distance(input.begin(), inputIt)));
    }

    ++inputIt;
}

std::unique_ptr<AST_Poly::Number> Parser_Poly::Impl::testInputForNumber()
{
    TRACE();
    skipWhitespace();
    if (inputIt == input.end())
    {
        return nullptr;
    }
    else
    {
        auto tmpIt = inputIt;
        if (*tmpIt == '-')
        {
            ++tmpIt;
        }

        while (tmpIt != input.end() and std::isdigit(*tmpIt))
        {
            ++tmpIt;
        }

        if (tmpIt != inputIt)
        {
            auto value = std::stoi(std::string{inputIt, tmpIt});
            auto number = std::make_unique<AST_Poly::Number>(value);
            inputIt = tmpIt;
            return number;
        }
        else
        {
            return nullptr;
        }
    }
}

bool Parser_Poly::Impl::testInput(char expected)
{
    TRACE();
    skipWhitespace();
    if (inputIt == input.end())
    {
        return false;
    }
    else
    {
        return *inputIt == expected;
    }
}

bool Parser_Poly::Impl::parsedAllInput()
{
    skipWhitespace();

    return (inputIt == input.end());
}

bool Parser_Poly::Impl::testForVariableName()
{
    skipWhitespace();
    if (parsedAllInput())
        return false;

    if (*inputIt == varName[0])
    {
        ++inputIt;
        return true;
    }
    else
    {
        return false;
    }
}

void Parser_Poly::Impl::advanceIfMatch(char expected)
{
    skipWhitespace();

    if (inputIt != input.end() and *inputIt == expected)
    {
        ++inputIt;
    }
}

void Parser_Poly::Impl::skipWhitespace()
{
    while (inputIt != input.end() and std::isspace(*inputIt))
    {
        ++inputIt;
    }
}
