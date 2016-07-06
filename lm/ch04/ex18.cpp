#include "parser.hpp"
#include "parser_ast.hpp"
#include "gtest/gtest.h"
#include <sstream>
#include <iostream>

TEST(LMCh04Ex18, willInstantiateParser)
{
    Parser p{"x = 123;"};

    ASSERT_TRUE(p.parse());
}

TEST(LMCh04Ex18, willInstantiateParserAst)
{
    Parser_Ast p{"xyzfff = 321;"};

    auto ast = p.parse();
    ASSERT_NE(nullptr, ast);

    std::stringstream out;
    AST::AstPrintingVisitor pv{out};
    pv.visit(*dynamic_cast<AST::Asignment*>(ast.get()));
    ASSERT_EQ("xyzfff <- 321", out.str());
}
