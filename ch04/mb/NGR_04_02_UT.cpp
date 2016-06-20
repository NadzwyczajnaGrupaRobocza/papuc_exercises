#include <vector>
#include "gtest/gtest.h"
#include "NGR_04_02_01.hpp"

TEST(MBB_04_02, printVectorTest)
{
	std::vector<double> data={-12.0, 23.6, 13.1};
	EXPECT_EQ("[-12.0, 23.6, 13.1]", showVector(data));
}
