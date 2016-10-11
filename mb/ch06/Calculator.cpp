#include <iostream>

#include "../common/Common.hpp"
#include "Token.hpp"
#include "TokenStream.hpp"
#include "Calculator.hpp"

void clean(ITokenStream& tokenStream)
{
    tokenStream.ignore(END_OF_EXPR);
}

Calculator::Calculator(ITokenStream& aTokenStream)
    : tokenStream {aTokenStream}
{    
}

double Calculator::expression()
{
    double left = term();
    Token token = tokenStream.get();
    while(true)
    {
        switch(token.kind)
        {
            case '+':
                left += term();
                token = tokenStream.get();
                break;
            case '-':
                left -= term();
                token = tokenStream.get();
                break;
            default:
                tokenStream.putback(token);
                return left;
        }
    }
}

double Calculator::term()
{
    double left = primary();
    Token token = tokenStream.get();
    while(true)
    {
        switch(token.kind)
        {
            case '*':
                left *= primary();
                token = tokenStream.get();
                break;
            case '/':
            {
                double right = primary();
                if (right == 0)
                {
                    throw std::logic_error("Dividing by 0");
                }
                left /= right;
                token = tokenStream.get();
                break;
            }
            case '%':
            {
                double right = primary();
                
                int iLeft = static_cast<int>(left);
                if (left != iLeft)
                {
                    throw std::logic_error("Left side of operation % should be integer number");
                }
                int iRight = static_cast<int>(right);
                if (right != iRight)
                {
                    throw std::logic_error("Right side of operation % should be integer number");
                }
                if (iRight == 0)
                {
                    throw std::logic_error("Dividing by 0");
                }
                left = iLeft % iRight;
                token = tokenStream.get(); 
                break;
            }
            default:
                tokenStream.putback(token);
                return left;
        }
    }
}

double Calculator::primary()
{
    Token token = tokenStream.get();
    double value = 0;
    switch(token.kind)
    {
        case '(':
        {
            value = expression();
            token = tokenStream.get();
            if( token.kind != ')' )
            {
                throw std::logic_error("Expected ')'");
            }
            return calculteValue(value);
        }
        case '{':
        {
            value = expression();
            token = tokenStream.get();
            if( token.kind != '}' )
            {
                throw std::logic_error("Expected '}'");
            }
            return calculteValue(value);
        }
        case NUMBER:
        {
            value = token.value;
            return calculteValue(value);
        }
        case QUIT:
        {
            tokenStream.putback(token);
            return 0.0;
        }
        default:
        {
            tokenStream.putback(token);
            std::string cause{"Expected czynnika, przekazano "};
            cause += token.kind;
            throw std::logic_error(cause);
            //return 0.0;
        }
    }
}

double Calculator::calculteValue(const double& value)
{
    Token token = tokenStream.get();
    if(token.kind == '!' )
    {
        return mbcommon::factorial(value);
    }
    else
    {
        tokenStream.putback(token);
        return value;
    }
}
