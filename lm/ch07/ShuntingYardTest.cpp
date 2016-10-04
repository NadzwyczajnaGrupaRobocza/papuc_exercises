#include "gtest/gtest.h"

#include "MockTokenStream.hpp"
#include "ShuntingYard.hpp"
#include "StreamLog.hpp"

using testing::Return;
using testing::InSequence;
namespace calc
{
class ShuntingYardTest : public testing::Test
{
protected:
    void next(Token t)
    {
        EXPECT_CALL(ts, _hasNext()).WillOnce(Return(true));
        EXPECT_CALL(ts, _get()).WillOnce(Return(t));
    }

    util::StreamLog log{std::cout};
    calc::MockTokenStream ts;
    calc::ASTBuilder astb{log, ts};
};

TEST_F(ShuntingYardTest, willCreateInstance)
{
    EXPECT_CALL(ts, _hasNext()).WillOnce(Return(false));
    ASSERT_EQ(astb.getAST(), nullptr);
}

TEST_F(ShuntingYardTest, willCreateTrivialTree)
{
    InSequence s;
    EXPECT_CALL(ts, _hasNext()).WillOnce(Return(true));
    EXPECT_CALL(ts, _get()).WillOnce(Return(Token{'8', 14.7}));
    EXPECT_CALL(ts, _hasNext()).WillOnce(Return(false));

    auto trivialTree = astb.getAST();

    ASSERT_EQ(trivialTree->left, nullptr);
    ASSERT_EQ(trivialTree->right, nullptr);
    ASSERT_EQ(trivialTree->data.typeId, '8');
    ASSERT_DOUBLE_EQ(trivialTree->data.value, 14.7);
}

TEST_F(ShuntingYardTest, willCreateSimpleTree)
{
    auto v2 = Token{'8', 4.1};
    auto v3 = Token{'8', 2.0};
    InSequence s;
    next(Token{'8', 14.7});
    next(Token{'+'});
    next(v2);
    next(Token{'*'});
    next(v3);
    EXPECT_CALL(ts, _hasNext()).WillOnce(Return(false));


    auto simpleTree = astb.getAST();

    ASSERT_NE(simpleTree->left, nullptr);
    ASSERT_NE(simpleTree->right, nullptr);
    ASSERT_EQ(simpleTree->data.typeId, '+');
    // ASSERT_DOUBLE_EQ(simpleTree->left->data.value, 14.7);
    // ASSERT_EQ(simpleTree->right->data.typeId, '*');
    // ASSERT_EQ(simpleTree->right->left->data, v2);
    // ASSERT_EQ(simpleTree->right->right->data, v3);
}

}
