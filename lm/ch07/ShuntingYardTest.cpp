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

    void nextId(const std::string& s)
    {
        next(Token{'S', s});
    }

    void endOfInput()
    {
        EXPECT_CALL(ts, _hasNext()).WillOnce(Return(false));
    }

    void validateLispyForm(ASTNode* tree, const std::string& expectedLisp)
    {
        ASSERT_EQ(lispyTreePrint(tree), expectedLisp) << logSink.str();
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

    validateLispyForm(trivialTree.get(), "14.7");
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

    validateLispyForm(simpleTree.get(), "(+ 14.7 (* 4.1 2.3))");
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

    validateLispyForm(simpleTree.get(), "(+ 14.7 (* 4.1 (- 1.5 0.7)))");
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

    validateLispyForm(unaryMinusTree.get(), "(* (# 12.3) (# (/ 16.7 10.5)))");
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

    validateLispyForm(unaryMinusTree.get(), "(* 12.3 (/ 16.7 10.5))");
}

TEST_F(ShuntingYardTest, willHandleSymbolAddition)
{
    InSequence s;
    nextId("x1");
    nextSym('+');
    nextVal(11.1);
    endOfInput();

    auto symbolTree = astb.getAST();

    validateLispyForm(symbolTree.get(), "(+ x1 11.1)");
}

TEST_F(ShuntingYardTest, willHandleValueAsignment)
{
    InSequence s;
    nextId("x1");
    nextSym('=');
    nextVal(11.1);
    endOfInput();

    auto symbolTree = astb.getAST();

    validateLispyForm(symbolTree.get(), "(= x1 11.1)");
}

TEST_F(ShuntingYardTest, willHandleValueAsignmentIncludingPrecedence)
{

    // x1 = 14.7 + 4.1 * (1.5 - 0.7)
    InSequence s;
    nextId("x1");
    nextSym('=');
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

    auto symbolTree = astb.getAST();

    validateLispyForm(symbolTree.get(), "(= x1 (+ 14.7 (* 4.1 (- 1.5 0.7))))");
}
}
