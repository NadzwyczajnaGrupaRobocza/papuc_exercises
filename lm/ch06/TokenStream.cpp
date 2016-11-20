#include "TokenStream.hpp"

#include <cctype>
#include <istream>
#include <sstream>
#include <string>
#include <vector>

#include <boost/range/algorithm.hpp>

namespace calc
{

TokenStream::TokenStream(std::istream& inputInit)
    : inputVal{nullptr}, input{inputInit}, bufferFull{false}
{
}

TokenStream::TokenStream(std::stringstream&& inputInitVal)
    : inputVal{std::make_unique<std::stringstream>(std::move(inputInitVal))},
      input{*inputVal}, bufferFull{false}
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
        case '(':
        case ')':
        case '{':
        case '}':
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '!':
            return Token{ch};
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
        default:
        {
            if (std::isalpha(ch) or ch == '_')
            {
                std::vector<char> l_buffer;
                l_buffer.reserve(32u);
                l_buffer.push_back(ch);

                ch = input.get();
                while (ch != std::istream::traits_type::eof() and
                       (std::isalnum(ch) or ch == '_'))
                {
                    l_buffer.push_back(ch);
                    ch = input.get();
                }

                if (not input.eof())
                {
                    input.putback(ch);
                }

                std::string idValue;
                idValue.reserve(l_buffer.size());
                boost::copy(l_buffer, std::back_inserter(idValue));

                return Token('S', idValue);
            }
            else
            {
                throw std::runtime_error("invalid char in input stream");
            }
        }
        }
    }
    else
    {
        return Token{'E'};
    }
}

bool TokenStream::hasNext()
{
    return not input.eof();
}
}
