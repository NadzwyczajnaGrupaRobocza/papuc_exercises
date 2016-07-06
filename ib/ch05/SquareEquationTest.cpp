#include "gtest/gtest.h"
#include "SquareEquation.h"


class SquareEquationTest : public ::testing::Test
{
	public:
	SquareEquation equation;
	void SetUp()
	{
	}
};

TEST_F(SquareEquationTest, deltaIsNonNegative)
{
	equation.setEquationEntries(1,1,-2);
	std::vector<float> result;
	result.push_back(1.);
	result.push_back(-2.);
	EXPECT_EQ(equation.solveEquation(), result);
}

TEST_F(SquareEquationTest, deltaIsNegative)
{
	equation.setEquationEntries(1,1,1);
	EXPECT_THROW(equation.solveEquation(), std::runtime_error);
}

TEST_F(SquareEquationTest, isNotSquare)
{
	equation.setEquationEntries(0,1,1);
	EXPECT_THROW(equation.solveEquation(), std::runtime_error);
}


