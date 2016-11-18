#include "LedTokenParserFactory.hpp"
#include "IMemory.hpp"
#include "LedLdState.hpp"
#include "LedOutState.hpp"
#include "RecognizeState.hpp"

namespace lz
{
std::unique_ptr<LedTokenParser>
LedTokenParserFactory::createRecognizeState() const
{
    return std::make_unique<RecognizeState>();
}

std::unique_ptr<LedTokenParser>
LedTokenParserFactory::createLedLdState(std::shared_ptr<IMemory> memory) const
{
    return std::make_unique<LedLdState>(memory);
}

std::unique_ptr<LedTokenParser> LedTokenParserFactory::createLedOutState(
    std::shared_ptr<const IMemory> memory) const
{
    return std::make_unique<LedOutState>(memory);
}
}
