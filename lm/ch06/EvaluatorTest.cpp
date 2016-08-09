#include "gtest/gtest.h"
#include "Evaluator.hpp"
#include "MockTokenStream.hpp"

using namespace testing;

class EvaluatorTest : public Test
{
public:
    EvaluatorTest()
    {}
protected:
    calc::MockTokenStream mts;
    calc::Evaluator e{mts};
};

TEST_F(EvaluatorTest, willAddTwoTokens)
{
    calc::Token val1{'8', 11.5};
    calc::Token plus{'+'};
    calc::Token val2{'8', 0.8};
    calc::Token terminate{';'};

    InSequence dummy;
    EXPECT_CALL(mts, _get()).WillOnce(Return(val1));
    EXPECT_CALL(mts, _get()).WillOnce(Return(plus));
    EXPECT_CALL(mts, _putback(plus)).Times(1);
    EXPECT_CALL(mts, _get()).WillOnce(Return(plus));
    EXPECT_CALL(mts, _get()).WillOnce(Return(val2));
    EXPECT_CALL(mts, _get()).WillOnce(Return(terminate));
    EXPECT_CALL(mts, _putback(terminate));
    EXPECT_CALL(mts, _get()).WillOnce(Return(terminate));
    ASSERT_EQ(e.expression(), 12.3);
}
