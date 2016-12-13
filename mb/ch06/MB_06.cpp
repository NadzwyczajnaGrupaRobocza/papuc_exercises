#include <iostream>
#include <stdexcept>

#include "Token.hpp"
#include "TokenStream.hpp"
#include "Calculator.hpp"

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cout << "There aren't any operations send to Calculator" << std::endl;
        return 1;
    }
    
    std::cout << ">> " << argv[1] << std::endl;
    
    std::string expression{argv[1]};
    TokenStream tokenStream{expression + END_OF_EXPR + QUIT};

    try
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
                    return 0;
                }
                tokenStream.putback(token);
                value = parser.expression();
                std::cout << "= " << value << std::endl;
            }
            catch (std::logic_error& error)
            {
                std::cerr << error.what() << std::endl;
                clean(tokenStream);
            }
        }
        return 0;
    }
    catch (std::logic_error& error)
    {
        std::cerr << error.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unexpected exception";
        return 2;
    }
}

