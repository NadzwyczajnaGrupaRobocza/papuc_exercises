#include "ShuntingYard.hpp"

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

ASTBuilder::ASTBuilder(util::Log& logInit, TokenStream& tsInit)
    : log{logInit}, ts{tsInit}
{
}

ASTBuilder::ASTBuilder(util::Log& logInit, TokenStream&& tsInit)
    : log{logInit}, tsVal{std::make_unique<TokenStream>(std::move(tsInit))},
      ts{*tsVal}
{
}

std::unique_ptr<ASTNode> ASTBuilder::getAST()
{
    while (ts.hasNext())
    {
        auto token = ts.get();
        log.debug() << "processing token: " << token << "\n";
        switch (token.typeId)
        {
        case '8':
        case 'S':
        {
            outStack.push(std::make_unique<ASTNode>(token));
            break;
        }
        case '+':
        case '-':
        {
            while (not opStack.empty() and
                   (opStack.top().typeId == '*' or opStack.top().typeId == '/'))
            {
                processBinaryPop(opStack.top());
                opStack.pop();
            }

            opStack.push(token);
            break;
        }
        case '*':
        case '/':
        {
            opStack.push(token);
            break;
        }
        default:
        {
            log.error() << "default should not happen\n";
        }
        }
    }

    while (not opStack.empty())
    {
        processBinaryPop(opStack.top());
        opStack.pop();
    }

    if (outStack.size() == 1u)
    {
        return std::move(outStack.top());
    }
    else
    {
        return nullptr;
    }
}

void ASTBuilder::processBinaryPop(const Token& opTok)
{
    if (outStack.size() < 2u)
    {
        throw std::logic_error("malformed expression");
    }
    else
    {
        auto rightArg = std::move(outStack.top());
        outStack.pop();
        auto leftArg = std::move(outStack.top());
        outStack.pop();

        outStack.push(std::make_unique<ASTNode>(opTok, std::move(leftArg),
                                                std::move(rightArg)));
    }
}
}
