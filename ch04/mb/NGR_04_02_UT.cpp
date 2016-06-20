#include <vector>
#include "gtest/gtest.h"
#include "NGR_04_02_01.hpp"

using std::vector;

TEST(MBB_04_02, printVectorTest)
{
	std::vector<double> data={-12.0, 23.6, 13.1};
	//printVector(data);
	EXPECT_EQ("[-12.0, 23.6, 13.1]", vectorToString(data));
}
