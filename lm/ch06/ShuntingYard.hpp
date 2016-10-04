#pragma once

#include <memory>
#include <stack>
#include "Log.hpp"
#include "Token.hpp"
#include "TokenStream.hpp"

namespace calc
{
class ASTNode
{
public:
    ASTNode(const Token&);
    ASTNode(Token&&);
    ASTNode(const Token&, std::unique_ptr<ASTNode>, std::unique_ptr<ASTNode>);
    ASTNode(Token&&, std::unique_ptr<ASTNode>, std::unique_ptr<ASTNode>);

    Token data;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
};

class ASTBuilder
{
public:
    ASTBuilder(util::Log&, TokenStream&);
    ASTBuilder(util::Log&, TokenStream&&);

    std::unique_ptr<ASTNode> getAST();
private:
    void processBinaryPop(const Token&);

    util::Log& log;
    std::unique_ptr<TokenStream> tsVal;
    TokenStream& ts;

    std::stack<std::unique_ptr<ASTNode>> outStack;
    std::stack<Token> opStack;
};
}
