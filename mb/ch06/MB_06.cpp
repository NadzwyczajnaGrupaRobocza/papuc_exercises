#include <iostream>
#include <stdexcept>

#include "MB_06_00.hpp"

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cout << "Nie podano parametru!" << std::endl;
        return 1;
    }
    
    std::cout << "Wyliczanie wyrażenia " << argv[1] << std::endl;
    
    std::string expression{argv[1]};    
    TokenStream tokenStream{expression + ";"};
    
    try
    {
        double value = 0;
        Parser parser{tokenStream};
        while (std::cin) // ??????????
        {
            Token token = tokenStream.get();
            if(token.kind == 'k')
            {
                break;
            }
            if(token.kind == ';')
            {
                std::cout << "=" << value << std::endl;
            }
            else
            {
                tokenStream.putback(token);
            }
            value = parser.expression();
        }
    }
    catch (std::logic_error& error)
    {
        std::cerr << error.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "Wyjątek";
        return 2;
    }
    return 0;
}
