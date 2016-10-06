#include "gmock/gmock.h"
#include "Token.hpp"
#include "TokenStream.hpp"

class Token;

class MockTokenStream : public ITokenStream
{
public:
    MOCKMETHOD0(get, Token);
    MOCKMETHOD1(putback, void(Token));
    MOCKMETHOD1(ignore, void(char));
};
