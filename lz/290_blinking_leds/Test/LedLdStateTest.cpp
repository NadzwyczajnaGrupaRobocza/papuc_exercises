#include <gtest/gtest.h>

#include <gsl/gsl_assert>

#include "LedLdState.hpp"
#include "LedToken.hpp"
#include "MemoryMock.hpp"
#include "Byte.hpp"

using namespace ::testing;
namespace lz
{
class LedLdStateTest : public ::Test
{
public:
    void expectSetRegisterA(const Byte& reg)
    {
        EXPECT_CALL(*memory, set_register_a(reg));
        EXPECT_EQ(
            LedTokenState::Recognize,
            ldCommand.parse(LedToken{"a," + std::to_string(reg.value())}));
    }

    void expectInvalidArgument(const LedToken& token)
    {
        EXPECT_THROW(ldCommand.parse(token), gsl::fail_fast);
    }

    void expectInvalidRegister(const LedToken& token)
    {
        EXPECT_THROW(ldCommand.parse(token), std::out_of_range);
    }

    std::shared_ptr<MemoryMock> memory =
        std::make_shared<StrictMock<MemoryMock>>();
    LedLdState ldCommand{memory};
};

TEST_F(LedLdStateTest, parse)
{
    expectSetRegisterA(Byte{255});
    expectSetRegisterA(Byte{0});
    expectSetRegisterA(Byte{133});
    expectSetRegisterA(Byte{85});
}

TEST_F(LedLdStateTest, invalidRange)
{
    expectInvalidArgument(LedToken{"a,-1"});
    expectInvalidArgument(LedToken{"a,-23"});
    expectInvalidArgument(LedToken{"a,256"});
}

TEST_F(LedLdStateTest, invalidRegister)
{
    expectInvalidRegister(LedToken{"b,1"});
    expectInvalidRegister(LedToken{"3,23"});
    expectInvalidRegister(LedToken{"h,134"});
}
}
