#include <gtest/gtest.h>
#include <memory>

#include "MemoryMock.hpp"
#include "UniqueMock.hpp"
#include "LedTokenParserMock.hpp"

#include "LedSimulationFsm.hpp"
#include "Byte.hpp"
#include "LedToken.hpp"

using namespace ::testing;

namespace lz
{
class LedSimulationFsmTest : public ::Test
{
public:
    void expectTransitTo(LedSimulationFsm& fsm, const LedToken& token,
                         const LedTokenState& tokenState,
                         ut::unique_mock<LedTokenParserMock>& mock)
    {
        EXPECT_CALL(*mock, parse(token)).WillOnce(Return(tokenState));
        fsm.parse(token);
    }

    ut::unique_mock<LedTokenParserMock> ldState;
    ut::unique_mock<LedTokenParserMock> outState;
    ut::unique_mock<LedTokenParserMock> recognizeState;
};

TEST_F(LedSimulationFsmTest, transition)
{
    LedSimulationFsm fsm{recognizeState.unique(), ldState.unique(),
                         outState.unique()};

    expectTransitTo(fsm, LedToken{"token"}, LedTokenState::LedLdCommand,
                    recognizeState);
    expectTransitTo(fsm, LedToken{"token"}, LedTokenState::Recognize, ldState);
    expectTransitTo(fsm, LedToken{"token"}, LedTokenState::Recognize,
                    recognizeState);
    expectTransitTo(fsm, LedToken{"token"}, LedTokenState::Recognize,
                    recognizeState);
    expectTransitTo(fsm, LedToken{"token"}, LedTokenState::LedOutCommand,
                    recognizeState);
}
}
