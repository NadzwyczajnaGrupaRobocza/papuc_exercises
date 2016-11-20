#include "SquareEquation.h"
#include "gtest/gtest.h"

class SquareEquationTest : public ::testing::Test
{
public:
};

TEST_F(SquareEquationTest, deltaIsNonNegative)
{
    std::vector<double> polynom{-2, 1, 1};
    SquareEquation equation(polynom);
    std::vector<double> result;
    result.push_back(1.);
    result.push_back(-2.);
    EXPECT_EQ(equation.solveEquation(), result);
}

TEST_F(SquareEquationTest, deltaIsNegative)
{
    std::vector<double> polynom{1, 1, 1};
    SquareEquation equation(polynom);
    EXPECT_THROW(equation.solveEquation(), std::runtime_error);
}

TEST_F(SquareEquationTest, DISABLED_isNotSquare)
{
    // fixme:
    // isSquare() method use square[2] which is invalid for polynom{1,1,0}
    // because only positive number is choosen to create Polynomial
    // square.size() == 2
    std::vector<double> polynom{1, 1, 0};
    SquareEquation equation(polynom);
    EXPECT_THROW(equation.solveEquation(), std::runtime_error);
}
