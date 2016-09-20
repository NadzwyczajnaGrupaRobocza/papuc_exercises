#include <stdexcept>
#include <iostream>

#include "MB_06_00.hpp"

int factorial(const unsigned& value)
{
    if(value == 0 or value == 1)
    {
        return 1;
    }
    else
    {
        return value * factorial(value -1);
    }
}

void error(std::string cause)
{
    std::logic_error logicError(cause);
    throw logicError;
}

Token::Token(char aKind)
    : kind {aKind}, value {0.0}
{
}

Token::Token(char aKind, double aValue)
    : kind {aKind}, value{aValue}
{
}

TokenStream::TokenStream() 
    : full {false}, buffer {0}
{
}

TokenStream::TokenStream(const std::string aString)
    : full {false}, buffer {0}, stream {aString}
{
}

Token TokenStream::get()
{
    if(full)
    {
        full = false;
        return buffer;
    }
    
    char ch;
    if(stream >> ch)
    {
        switch(ch)
        {
            case ';':
            case 'k':
            case '(': case ')': case '{': case '}':
            case '!':
            case '*': case '/':
            case '+': case '-':
            {
                return Token(ch);
            }
            
            case '.':
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            {
                stream.putback(ch);
                double value;
                stream >> value;
                return Token{'d', value};
            }
            default:
            {
                std::stringstream wrongToken;
                wrongToken << "Nieprawidłowy token:" << ch << std::endl
                           << "Kod: " << static_cast<int>(ch) << std::endl;
                std::logic_error error(wrongToken.str());
                throw error;
            }
            
        }
    }
    else // zastąpić w rozsądny sposób
    {
        std::cout << "Returning token #" << std::endl;
        return Token{'#'};
    }
}

void TokenStream::putback(Token token)
{
    if(full)
    {
        error("Wstawianie tokenu do pełnego bufora");
    }
    buffer = token;
    full = true;
}

Parser::Parser(TokenStream& aTokenStream)
    : tokenStream {aTokenStream}
{    
}

double Parser::expression()
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

double Parser::term()
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
                    std::logic_error error("Dzielenie przez 0");
                    throw error;
                }
                left /= right;
                token = tokenStream.get();
                break;
            }
            default:
                tokenStream.putback(token);
                return left;
        }
    }
}

double Parser::primary()
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
                std::logic_error error("Oczekiwano ')'");
                throw error;
            }
            return calculteValue(value);
        }
        case '{':
        {
            value = expression();
            token = tokenStream.get();
            if( token.kind != '}' )
            {
                std::logic_error error("Oczekiwano '}'");
                throw error;
            }
            return calculteValue(value);
        }
        case 'd':
        {
            value = token.value;
            return calculteValue(value);
        }
        case 'k':
        {
            tokenStream.putback(token);
            return 0.0;
        }
        default:
        {
            tokenStream.putback(token);
            std::cout << "Token: " << token.kind << std::endl;
            std::logic_error error("Oczekiwano czynnika");
            throw error;
        }
    }
}

double Parser::calculteValue(const double& value)
{
    Token token = tokenStream.get();
    if(token.kind == '!' )
    {
        return factorial(value);
    }
    else
    {
        tokenStream.putback(token);
        return value;
    }
}
