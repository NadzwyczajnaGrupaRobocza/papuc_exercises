#include <gtest/gtest.h>

#include "UniqueMock.hpp"
#include <gsl/gsl_assert>

using namespace ::testing;

namespace ut
{
class ITest
{
public:
    virtual ~ITest() = default;
    virtual void doSth() const = 0;
};
class ITestMock : public ITest
{
public:
    MOCK_CONST_METHOD0(doSth, void());
};

TEST(UniqueMockTest, get)
{
    ut::unique_mock<ITestMock> test_mock;
    ASSERT_NE(nullptr, test_mock.get());
}

TEST(UniqueMockTest, unique_cleanupAfterDestroy)
{
    ut::unique_mock<ITestMock> test_mock;
    {
        std::unique_ptr<ITest> test = test_mock.unique();
        ASSERT_EQ(nullptr, test_mock.release());
        ASSERT_NE(nullptr, test_mock.get());
        ASSERT_NE(nullptr, test.get());
    }
    ASSERT_EQ(nullptr, test_mock.get());
}

TEST(UniqueMockTest, usingDestroyedObject_shouldThrow)
{
    ut::unique_mock<ITestMock> test_mock;
    {
        std::unique_ptr<ITest> test = test_mock.unique();
    }
    EXPECT_THROW(*test_mock, gsl::fail_fast);
    EXPECT_THROW(test_mock->doSth(), gsl::fail_fast);
}
}
