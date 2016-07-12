#include "Parser_Poly.hpp"
#include "parser.hpp"
#include "parser_ast.hpp"
#include "gtest/gtest.h"
#include <iostream>
#include <sstream>

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

TEST(LMCh04Ex18, willParsePolyAndBuildCorrectVector)
{
    Parser_Poly p{"-2 * x ^ 2 + 3 * x - 1"};
    auto ast = p.parse();
    AST_Poly::PolyBuilder pb;
    auto polyCoeffs = pb.getPolyCoeffsFromAst(*ast);
    auto expectedCoeffs = std::vector<int>{-1, 3, -2};
    ASSERT_EQ(expectedCoeffs, polyCoeffs);
}

TEST(LMCh04Ex18, willParsePolyOfFifthDegree)
{
    Parser_Poly p{"10 x ^ 5 + -2 * x ^ 2 + 3 * x - 1"};
    auto ast = p.parse();
    AST_Poly::PolyBuilder pb;
    auto polyCoeffs = pb.getPolyCoeffsFromAst(*ast);
    auto expectedCoeffs = std::vector<int>{-1, 3, -2, 0, 0, 10};
    ASSERT_EQ(expectedCoeffs, polyCoeffs);
}
