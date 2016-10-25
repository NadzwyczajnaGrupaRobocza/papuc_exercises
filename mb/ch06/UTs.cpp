#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MockTokenStream.hpp"

#include "Token.hpp"
#include "Calculator.hpp"

using testing::InSequence;
using testing::AtLeast;
using testing::Return;

TEST(MBB_06, basicScenario)
{
//    MockTokenStream mTokenStream{};
//    
//    InSequence seq;
//    std::vector<Token> tokens;
//    tokens.push_back(Token{NUMBER, '2'});
//    
//    EXPECT_CALL(mTokenStream, get()).Times(1).WillOnce(Return(tokens[0]));
//    EXPECT_CALL(mTokenStream, putback(tokens[0])).Times(1);
//
//    Calculator calculator{mTokenStream};
//    calculator.expression();
    ASSERT_TRUE(12); 
}
