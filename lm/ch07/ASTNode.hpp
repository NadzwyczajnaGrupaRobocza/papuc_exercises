#pragma once

#include <memory>
#include "Token.hpp"
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

std::string lispyTreePrint(ASTNode*);
