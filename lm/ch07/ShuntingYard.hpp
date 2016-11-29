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
    ASTBuilder(common::Log&, TokenStream&);
    ASTBuilder(common::Log&, TokenStream&&);

    std::unique_ptr<ASTNode> getAST();

private:
    void processOp(const Token& opTok);
    bool hasLowerPrecedenceThanStackTop(const Token& opTok);
    bool isBinaryOp(const Token& opTok);
    bool isUnaryOp(const Token& opTok);
    void processBinaryPop(const Token&);
    void processUnaryPop(const Token& opTok);

    common::Log& log;
    std::unique_ptr<TokenStream> tsVal;
    TokenStream& ts;

    std::stack<std::unique_ptr<ASTNode>> outStack;
    std::stack<Token> opStack;
};

class ASTEvaluator
{
public:
    ASTEvaluator(common::Log&, SymbolTable&);

    double evaluate(ASTNode*);
private:
    common::Log& log;
    SymbolTable& st;
};
}
