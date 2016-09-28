#include <iostream>

#include "../common/Common.hpp"
#include "Token.hpp"
#include "TokenStream.hpp"
#include "Calculator.hpp"


void clean(TokenStream& tokenStream)
{
    tokenStream.ignore(END_OF_EXPR);
}

Calculator::Calculator(TokenStream& aTokenStream)
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
                    //std::logic_error error("Dzielenie przez 0");
                    //throw error;
                    mbcommon::error("Dzielenie przez 0");
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
                    mbcommon::error("Lewa strona działania % nie jest liczbą całkowitą");
                }
                int iRight = static_cast<int>(right);
                if (right != iRight)
                {
                    mbcommon::error("Prawa strona działania % nie jest liczbą całkowitą");
                }
                if (iRight == 0)
                {
                    mbcommon::error("Dzielenie przez 0");
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
                //std::logic_error error("Oczekiwano ')'");
                //throw error;
                mbcommon::error("Oczekiwano ')'");
            }
            return calculteValue(value);
        }
        case '{':
        {
            value = expression();
            token = tokenStream.get();
            if( token.kind != '}' )
            {
                //std::logic_error error("Oczekiwano '}'");
                //throw error;
                mbcommon::error("Oczekiwano '}'");
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
            std::string cause{"Oczekiwano czynnika, przekazano "};
            cause += token.kind;
            //std::logic_error error(cause);
            //throw error;
            mbcommon::error(cause);
            return 0.0;
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
