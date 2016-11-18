#pragma once
#include <gmock/gmock.h>

#include "LedTokenParser.hpp"
#include "LedTokenParserFactory.hpp"

namespace lz
{
class IMemory;
class LedTokenParserFactoryMock : public LedTokenParserFactory
{
public:
    MOCK_CONST_METHOD0(_createRecognizeState, LedTokenParser*());
    MOCK_CONST_METHOD1(_createLedLdState,
                       LedTokenParser*(std::shared_ptr<IMemory>));

    MOCK_CONST_METHOD1(_createLedOutState,
                       LedTokenParser*(std::shared_ptr<const IMemory>));

    std::unique_ptr<LedTokenParser> createRecognizeState() const override
    {
        return std::unique_ptr<LedTokenParser>(_createRecognizeState());
    }

    std::unique_ptr<LedTokenParser>
    createLedLdState(std::shared_ptr<IMemory> memory) const override
    {
        return std::unique_ptr<LedTokenParser>(_createLedLdState(memory));
    }

    std::unique_ptr<LedTokenParser>
    createLedOutState(std::shared_ptr<const IMemory> memory) const override
    {
        return std::unique_ptr<LedTokenParser>(_createLedOutState(memory));
    }
};
}
