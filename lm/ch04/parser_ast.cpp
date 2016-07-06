#include "parser_ast.hpp"

#include <cctype>
#include <stdexcept>

class Parser_Ast::Impl
{
public:
    Impl(const std::string &);
    std::unique_ptr<AST::Node> parse();

private:
    std::unique_ptr<AST::Node> parseGoal();
    std::unique_ptr<AST::Asignment> parseAsignment();
    std::unique_ptr<AST::Symbol> parseLHS();
    std::unique_ptr<AST::Terminal> parseRHS();
    bool parseEqualsign();
    bool parseSemicolon();
    std::unique_ptr<AST::Symbol> parseIdentifier();
    std::unique_ptr<AST::Number> parseNumber();
    bool testInputAndAdvance(char);
    std::unique_ptr<AST::Symbol> testInputForIdentifier();
    std::unique_ptr<AST::Number> testInputForNumber();
    void skipWhitespace();

    std::string input;
    std::string::iterator inputIt;
};

Parser_Ast::Parser_Ast(const std::string &inputInitializer)
    : impl{std::make_unique<Impl>(inputInitializer)}
{
}

Parser_Ast::~Parser_Ast()
{
}

std::unique_ptr<AST::Node> Parser_Ast::parse()
{
    return impl->parse();
}

Parser_Ast::Impl::Impl(const std::string &inputInitializer)
    : input{inputInitializer}, inputIt{input.begin()}
{
}

std::unique_ptr<AST::Node> Parser_Ast::Impl::parse()
{
    return parseGoal();
}

std::unique_ptr<AST::Node> Parser_Ast::Impl::parseGoal()
{
    return parseAsignment();
}

std::unique_ptr<AST::Asignment> Parser_Ast::Impl::parseAsignment()
{
    auto lhs = parseLHS();
    if (lhs == nullptr)
    {
        return nullptr;
    }

    if (not parseEqualsign())
    {
        throw std::logic_error("failed to parse =");
    }

    auto rhs = parseRHS();
    if (rhs == nullptr)
    {
        throw std::logic_error("failed to parse rhs");
    }

    if (not parseSemicolon())
    {
        throw std::logic_error("failed to parse ;");
    }
    return std::make_unique<AST::Asignment>(std::move(lhs), std::move(rhs));
}

std::unique_ptr<AST::Symbol> Parser_Ast::Impl::parseLHS()
{
    return parseIdentifier();
}

std::unique_ptr<AST::Terminal> Parser_Ast::Impl::parseRHS()
{
    std::unique_ptr<AST::Terminal> id = parseIdentifier();
    if (id != nullptr)
    {
        return id;
    }

    return parseNumber();
}

bool Parser_Ast::Impl::parseEqualsign()
{
    return testInputAndAdvance('=');
}

bool Parser_Ast::Impl::parseSemicolon()
{
    return testInputAndAdvance(';');
}

std::unique_ptr<AST::Symbol> Parser_Ast::Impl::parseIdentifier()
{
    return testInputForIdentifier();
}

std::unique_ptr<AST::Number> Parser_Ast::Impl::parseNumber()
{
    return testInputForNumber();
}

bool Parser_Ast::Impl::testInputAndAdvance(char expected)
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

std::unique_ptr<AST::Symbol> Parser_Ast::Impl::testInputForIdentifier()
{
    skipWhitespace();
    if (inputIt == input.end())
    {
        return nullptr;
    }
    else
    {
        auto tmpIt = inputIt;
        while (tmpIt != input.end() and std::isalpha(*tmpIt))
        {
            ++tmpIt;
        }

        if (tmpIt != inputIt)
        {
            auto symbol =
                std::make_unique<AST::Symbol>(std::string(inputIt, tmpIt));
            inputIt = tmpIt;
            return symbol;
        }
        else
        {
            return nullptr;
        }
    }
}

std::unique_ptr<AST::Number> Parser_Ast::Impl::testInputForNumber()
{
    skipWhitespace();
    if (inputIt == input.end())
    {
        return nullptr;
    }
    else
    {
        auto tmpIt = inputIt;
        while (tmpIt != input.end() and std::isdigit(*tmpIt))
        {
            ++tmpIt;
        }

        if (tmpIt != inputIt)
        {
            auto value = std::stoi(std::string{inputIt, tmpIt});
            auto number = std::make_unique<AST::Number>(value);
            inputIt = tmpIt;
            return number;
        }
        else
        {
            return nullptr;
        }
    }
}

void Parser_Ast::Impl::skipWhitespace()
{
    while (inputIt != input.end() and std::isspace(*inputIt))
    {
        ++inputIt;
    }
}
