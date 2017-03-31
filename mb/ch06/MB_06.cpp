#include <iostream>
#include <stdexcept>

#include "Token.hpp"
#include "TokenStream.hpp"
#include "Calculator.hpp"

void cleanUpMess(ITokenStream& tokenStream);
void calculate(ITokenStream& tokenStream);
TokenStream passArgsToTokenStream(const char* argv[]);

int main(int argc, const char* argv[])
{
    if(argc < 2)
    {
        std::cout << "There aren't any operations send to Calculator" << std::endl;
        return 1;
    }

    TokenStream tokenStream = passArgsToTokenStream(argv);
    
    try
    {
        calculate(tokenStream);
        return 0;
    }
    catch (std::logic_error& error)
    {
        std::cerr << error.what() << std::endl;
        clean(tokenStream);
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unexpected exception";
        return 2;
    }
}

void cleanUpMess(ITokenStream& tokenStream)
{
    tokenStream.ignore(END_OF_EXPR);
}

void calculate(ITokenStream& tokenStream)
{
    double value = 0;
    Calculator parser{tokenStream};
    while (std::cin)
    {
        try
        {
            Token token = tokenStream.get();
            while (token.kind == END_OF_EXPR)
            {
                token = tokenStream.get();
            }
            if(token.kind == QUIT)
            {
                return;
            }
            tokenStream.putback(token);
            value = parser.expression();
            std::cout << "= " << value << std::endl;
        }
        catch (std::logic_error& error)
        {
            std::cerr << error.what() << std::endl;
            cleanUpMess(tokenStream);
        }
    }
}

TokenStream passArgsToTokenStream(const char* argv[])
{
    std::cout << ">> " << argv[1] << std::endl;
    
    std::string expression{argv[1]};
    TokenStream tokenStream{expression + END_OF_EXPR + QUIT};
    return tokenStream;
}
