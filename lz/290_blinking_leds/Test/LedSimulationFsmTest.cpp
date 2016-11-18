#include <gtest/gtest.h>
#include <memory>

#include "LedSimulationFsm.hpp"
#include "LedTokenParserFactoryMock.hpp"
#include "LedTokenParserMock.hpp"
#include "MemoryMock.hpp"
#include "UniqueMock.hpp"

#include "LedToken.hpp"
#include "Register.hpp"

using namespace ::testing;

namespace lz
{
class LedSimulationFsmTest : public ::Test
{
public:
    void expectCreateFactory()
    {
        EXPECT_CALL(factory, _createRecognizeState())
            .WillOnce(Return(recognizeState.release()));
        EXPECT_CALL(factory, _createLedLdState(memory))
            .WillOnce(Return(ldState.release()));

        std::shared_ptr<const IMemory> cmemory{memory};
        EXPECT_CALL(factory, _createLedOutState(cmemory))
            .WillOnce(Return(outState.release()));
    }

    void expectTransitTo(LedSimulationFsm& fsm, const LedToken& token,
                         const LedTokenState& tokenState,
                         ut::unique_mock<LedTokenParserMock>& mock)
    {
        EXPECT_CALL(*mock, parse(token)).WillOnce(Return(tokenState));
        fsm.parse(token);
    }

    StrictMock<LedTokenParserFactoryMock> factory;
    ut::unique_mock<LedTokenParserMock> ldState;
    ut::unique_mock<LedTokenParserMock> outState;
    ut::unique_mock<LedTokenParserMock> recognizeState;
    std::shared_ptr<IMemory> memory =
        std::make_shared<StrictMock<MemoryMock>>();
};

TEST_F(LedSimulationFsmTest, transition)
{
    expectCreateFactory();

    LedSimulationFsm fsm{factory, memory};
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
