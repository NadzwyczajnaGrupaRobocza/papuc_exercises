#include "ASTNode.hpp"

namespace calc
{
ASTNode::ASTNode(const Token& tokenInit)
    : data{tokenInit}, left{nullptr}, right{nullptr}
{
}

ASTNode::ASTNode(Token&& tokenInit) : data{std::move(tokenInit)}
{
}

ASTNode::ASTNode(const Token& tokenInit, std::unique_ptr<ASTNode> leftInit,
                 std::unique_ptr<ASTNode> rightInit)
    : data{tokenInit}, left{std::move(leftInit)}, right{std::move(rightInit)}
{
}

ASTNode::ASTNode(Token&& tokenInit, std::unique_ptr<ASTNode> leftInit,
                 std::unique_ptr<ASTNode> rightInit)
    : data{std::move(tokenInit)}, left{std::move(leftInit)},
      right{std::move(rightInit)}
{
}
}
