#include <gtest/gtest.h>
#include <boost/range/adaptor/transformed.hpp>

class T : public ::testing::Test
{
public:
    virtual ~T(){}
};

TEST_F(T, test1)
{
    EXPECT_TRUE(true);
}
