#pragma once

#include "Log.hpp"
#include "Token.hpp"
#include "TokenStream.hpp"
#include <memory>
#include <stack>
#include "SymbolTable.hpp"
#include "ASTNode.hpp"

namespace calc
{

class ASTBuilder
{
public:
    ASTBuilder(util::Log&, TokenStream&);
    ASTBuilder(util::Log&, TokenStream&&);

    std::unique_ptr<ASTNode> getAST();

private:
    void processOp(const Token& opTok);
    bool hasLowerPrecedenceThanStackTop(const Token& opTok);
    bool isBinaryOp(const Token& opTok);
    bool isUnaryOp(const Token& opTok);
    void processBinaryPop(const Token&);
    void processUnaryPop(const Token& opTok);

    util::Log& log;
    std::unique_ptr<TokenStream> tsVal;
    TokenStream& ts;

    std::stack<std::unique_ptr<ASTNode>> outStack;
    std::stack<Token> opStack;
};

class ASTEvaluator
{
public:
    ASTEvaluator(util::Log&, calc::SymbolTable&);

    double evaluate(ASTNode*);
private:
    util::Log& log;
    calc::SymbolTable& st;
};
}
