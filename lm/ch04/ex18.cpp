#include "parser.hpp"
#include "parser_ast.hpp"
#include "Parser_Poly.hpp"
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

TEST(LMCh04Ex18, willParsePolyWithNegativeCoeff)
{
    Parser_Poly p{"2 * x ^ 2 + 3 * x - 1"};
    auto ast = p.parse();
    AST_Poly::AstPrintingVisitor pv{std::cout};
    pv.visit(*ast);

}

TEST(LMCh04Ex18, willParsePolyWithNegativeLeadCoeff)
{
    Parser_Poly p{"- 2 * x ^ 2 + 3 * x - 1"};
    auto ast = p.parse();
    AST_Poly::AstPrintingVisitor pv{std::cout};
    pv.visit(*ast);

}
