#include "Parser_Poly.hpp"

#include <cctype>

class Parser_Poly::Impl
{
public:
    Impl(const std::string &);
    std::unique_ptr<AST_Poly::Poly> parse();

private:
    std::unique_ptr<AST_Poly::Poly> parsePoly();
    std::unique_ptr<AST_Poly::Mono> parseMono();
    std::unique_ptr<AST_Poly::Coeff> parseCoeffGroup();
    std::unique_ptr<AST_Poly::CoeffIdx> parseVarPow();
    bool parsePlusMinus();
    bool parseMult();
    bool parsePow();

    std::string input;
    std::string::iterator inputIt;
};

Parser_Poly::Parser_Poly(const std::string &inputInit)
    : impl{std::make_unique<Init>(inputInit)}
{
}

Parser_Poly::~Parser_Poly()
{
}

std::unique_ptr<AST_Poly::Poly> Parser_Poly::parse()
{
    return impl->parse();
}

Parser_Poly::Impl::Impl(const std::string &inputInit)
    : input{inputInit}, inputIt{input.begin()}
{
}

std::unique_ptr<AST_Poly::Poly> Parser_Poly::Impl::parse()
{
    return parsePoly();
}

std::unique_ptr<AST_Poly::Poly> Parser_Poly::Impl::parsePoly()
{
    if (parsedAllInput())
    {
        return nullptr;
    }

    auto mono = parseMono();
    if (mono == nullptr)
    {
        return nullptr;
    }

    return std::make_unique<AST_Poly::Poly>(std::move(mono), parsePoly());
}

std::unique_ptr<AST_Poly::Mono> Parser_Poly::Impl::parseMono()
{
    return nullptr;
}
