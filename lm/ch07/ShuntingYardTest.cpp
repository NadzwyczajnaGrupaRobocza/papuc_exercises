#include "gtest/gtest.h"

#include "MockTokenStream.hpp"
#include "ShuntingYard.hpp"
#include "StreamLog.hpp"
#include <iostream>
#include <sstream>

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

    void nextVal(double d)
    {
        next(Token{'8', d});
    }

    void nextSym(char s)
    {
        next(Token{s});
    }

    void endOfInput()
    {
        EXPECT_CALL(ts, _hasNext()).WillOnce(Return(false));
    }

    void validateTreesLispyForm(ASTNode* tree, const std::string& expectedLisp)
    {
        ASSERT_EQ(lispyTreePrint(tree), expectedLisp);
    }

    std::stringstream logSink;
    util::StreamLog log{logSink};
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
    nextVal(14.7);
    endOfInput();

    auto trivialTree = astb.getAST();

    validateTreesLispyForm(trivialTree.get(), "14.7");
}

TEST_F(ShuntingYardTest, willCreateSimpleTree)
{
    InSequence s;
    // 14.7 + 4.1 * 2.3
    nextVal(14.7);
    nextSym('+');
    nextVal(4.1);
    nextSym('*');
    nextVal(2.3);
    endOfInput();

    auto simpleTree = astb.getAST();

    validateTreesLispyForm(simpleTree.get(), "(+ 14.7 (* 4.1 2.3))");
}

TEST_F(ShuntingYardTest, willCreateSimpleTreeWithParens)
{
    // 14.7 + 4.1 * (1.5 - 0.7)
    InSequence s;
    nextVal(14.7);
    nextSym('+');
    nextVal(4.1);
    nextSym('*');
    nextSym('(');
    nextVal(1.5);
    nextSym('-');
    nextVal(0.7);
    nextSym(')');
    endOfInput();

    auto simpleTree = astb.getAST();

    validateTreesLispyForm(simpleTree.get(), "(+ 14.7 (* 4.1 (- 1.5 0.7)))");
}

TEST_F(ShuntingYardTest, willHandleUnaryMinus)
{
    InSequence s;
    // - 12.3 * - (16.7 / 10.5)
    nextSym('-');
    nextVal(12.3);
    nextSym('*');
    nextSym('-');
    nextSym('(');
    nextVal(16.7);
    nextSym('/');
    nextVal(10.5);
    nextSym(')');
    endOfInput();

    auto unaryMinusTree = astb.getAST();

    validateTreesLispyForm(unaryMinusTree.get(),
                           "(* (# 12.3) (# (/ 16.7 10.5)))");
}

TEST_F(ShuntingYardTest, willHandleUnaryPlus)
{
    InSequence s;
    // + 12.3 * + (16.7 / 10.5)
    nextSym('+');
    nextVal(12.3);
    nextSym('*');
    nextSym('+');
    nextSym('(');
    nextVal(16.7);
    nextSym('/');
    nextVal(10.5);
    nextSym(')');
    endOfInput();

    auto unaryMinusTree = astb.getAST();

    validateTreesLispyForm(unaryMinusTree.get(), "(* 12.3 (/ 16.7 10.5))");
}
}
