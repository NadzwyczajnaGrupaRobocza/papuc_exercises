#include "parser.hpp"

#include <cctype>
#include <stdexcept>

class Parser::Impl
{
public:
    Impl(const std::string&);
    bool parse();

private:
    bool parseGoal();
    bool parseAsignment();
    bool parseLHS();
    bool parseRHS();
    bool parseEqualsign();
    bool parseSemicolon();
    bool parseIdentifier();
    bool parseNumber();
    bool testInputAndAdvance(char);
    bool testInputForIdentifier();
    bool testInputForNumber();
    void skipWhitespace();

    std::string input;
    std::string::iterator inputIt;
};

Parser::Parser(const std::string& inputInitializer)
    : impl{std::make_unique<Impl>(inputInitializer)}
{
}

Parser::~Parser()
{
}

bool Parser::parse()
{
    return impl->parse();
}

Parser::Impl::Impl(const std::string& inputInitializer)
    : input{inputInitializer}, inputIt{input.begin()}
{
}

bool Parser::Impl::parse()
{
    return parseGoal();
}

bool Parser::Impl::parseGoal()
{
    return parseAsignment();
}

bool Parser::Impl::parseAsignment()
{
    if (not parseLHS())
    {
        return false;
    }

    if (not parseEqualsign())
    {
        throw std::logic_error("failed to parse =");
    }

    if (not parseRHS())
    {
        throw std::logic_error("failed to parse rhs");
    }

    if (not parseSemicolon())
    {
        throw std::logic_error("failed to parse ;");
    }
    return true;
}

bool Parser::Impl::parseLHS()
{
    return parseIdentifier();
}

bool Parser::Impl::parseRHS()
{
    if (parseIdentifier())
    {
        return true;
    }

    return parseNumber();
}

bool Parser::Impl::parseEqualsign()
{
    return testInputAndAdvance('=');
}

bool Parser::Impl::parseSemicolon()
{
    return testInputAndAdvance(';');
}

bool Parser::Impl::parseIdentifier()
{
    return testInputForIdentifier();
}

bool Parser::Impl::parseNumber()
{
    return testInputForNumber();
}

bool Parser::Impl::testInputAndAdvance(char expected)
{
    skipWhitespace();
    if (inputIt == input.end())
    {
        return false;
    }
    else
    {
        return *inputIt++ == expected;
    }
}

bool Parser::Impl::testInputForIdentifier()
{
    skipWhitespace();
    if (inputIt == input.end())
    {
        return false;
    }
    else
    {
        auto tmpPos = inputIt;
        while (tmpPos != input.end() and std::isalpha(*tmpPos))
        {
            ++tmpPos;
        }

        if (tmpPos != inputIt)
        {
            inputIt = tmpPos;
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool Parser::Impl::testInputForNumber()
{
    skipWhitespace();
    if (inputIt == input.end())
    {
        return false;
    }
    else
    {
        auto tmpPos = inputIt;
        while (tmpPos != input.end() and std::isdigit(*tmpPos))
        {
            ++tmpPos;
        }

        if (tmpPos != inputIt)
        {
            inputIt = tmpPos;
            return true;
        }
        else
        {
            return false;
        }
    }
}

void Parser::Impl::skipWhitespace()
{
    while (inputIt != input.end() and std::isspace(*inputIt))
    {
        ++inputIt;
    }
}
