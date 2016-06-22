#include <vector>
#include "gtest/gtest.h"
#include "NGR_04_02_01.hpp"

TEST(MBB_04_02, showVector)
{
    std::vector<double> data={-12.0, 23.6, 13.1};
    EXPECT_EQ("[-12, 23.6, 13.1]", showVector(data));
}

TEST(MBB_04_02, getMedianaFromOddVector)
{
    std::vector<double> data={100.3, -23.2, -12.0, 23.6, 13.1};
    EXPECT_EQ(13.1, getMediana(data));
}


TEST(MBB_04_02, getMedianaFromEvenVector)
{
    std::vector<double> data={-12.0, 23.6, 13.1, 42.66};
    EXPECT_EQ(18.35, getMediana(data));
}
