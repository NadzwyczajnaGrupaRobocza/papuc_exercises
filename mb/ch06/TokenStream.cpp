#include <iostream>

#include "../common/Common.hpp"
#include "Token.hpp"
#include "TokenStream.hpp"

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
            case END_OF_EXPR:
            case QUIT:
            case '(': case ')': case '{': case '}':
            case '!':
            case '*': case '/': case '%':
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
                return Token{NUMBER, value};
            }
            default:
            {
                std::stringstream wrongToken;
                //std::logic_error error(wrongToken.str());
                //throw error;
                mbcommon::error(wrongToken.str());
                return Token{'0'};
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
        mbcommon::error("Wstawianie tokenu do pełnego bufora");
    }
    buffer = token;
    full = true;
}

void TokenStream::ignore(char c)
{
    if(full && c == buffer.kind)
    {
        full = false;
        return;
    }
    full = false;
    char ch = 0;
    while(stream>>ch)
    {
        if(ch == c)
        {
            return;
        }
    }
}
