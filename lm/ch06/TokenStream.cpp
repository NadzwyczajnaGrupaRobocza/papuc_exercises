#include "TokenStream.hpp"

#include <istream>
#include <sstream>
namespace calc
{

TokenStream::TokenStream(std::istream& inputInit)
    : inputVal{nullptr}, input{inputInit}, bufferFull{false}
{
}

TokenStream::TokenStream(std::stringstream&& inputInitVal)
    : inputVal{std::make_unique<std::stringstream>(std::move(inputInitVal))},
      input{*inputVal},
      bufferFull{false}
{
}

Token TokenStream::get()
{
    if (bufferFull)
    {
        bufferFull = false;
        return buffer;
    }
    return getTokenFromStream();
}

void TokenStream::putback(Token t)
{
    buffer = t;
    bufferFull = true;
}

Token TokenStream::getTokenFromStream()
{
    char ch;
    if (input >> ch)
    {

    switch (ch)
    {
    case ';':
    case 'q':
    case '(':
    case ')':
    case '{':
    case '}':
    case '+':
    case '-':
    case '*':
    case '/':
    case '!': return Token{ch};
    case '.':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    {
        input.putback(ch);
        double value;
        input >> value;
        return Token('8', value);
    }
    default: throw std::runtime_error("invalid char in input stream");
    }
    }
    else
    {
        return Token{'E'};
    }
}
}
