#include <boost/range/adaptor/transformed.hpp>
#include <gtest/gtest.h>

class T : public ::testing::Test
{
public:
    virtual ~T()
    {
    }
};

TEST_F(T, test1)
{
    EXPECT_TRUE(true);
}

TEST(F, test2)
{
    EXPECT_TRUE(true);
}
