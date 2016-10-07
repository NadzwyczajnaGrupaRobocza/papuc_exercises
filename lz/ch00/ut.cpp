#include <gtest/gtest.h>

class T : public ::testing::Test
{
public:
    virtual ~T(){}
};

TEST_F(T, test1)
{
    EXPECT_TRUE(true);
}
