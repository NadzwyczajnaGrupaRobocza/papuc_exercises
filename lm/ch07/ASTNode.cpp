#include "ASTNode.hpp"
#include <sstream>

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

std::string lispyTreePrint(ASTNode* root)
{
    std::stringstream output;

    if (root != nullptr)
    {
        if (root->data.typeId != '8' and root->data.typeId != 'S')
        {
            output << '(';
            output << root->data.typeId << ' ';
            if (root->left != nullptr)
            {
                output << lispyTreePrint(root->left.get()) << ' ';
            }
            if (root->right != nullptr)
            {
                output << lispyTreePrint(root->right.get());
            }
            output << ')';
        }
        else if (root->data.typeId == '8')
        {
            output << root->data.value;
        }
        else if (root->data.typeId == 'S')
        {
            output << root->data.id;
        }
    }
    return output.str();
}
}
