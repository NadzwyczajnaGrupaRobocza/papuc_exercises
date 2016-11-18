#pragma once
#include <memory>

namespace lz
{
class IMemory;
class LedTokenParser;
class LedTokenParserFactory
{
public:
    virtual ~LedTokenParserFactory() = default;
    virtual std::unique_ptr<LedTokenParser> createRecognizeState() const;
    virtual std::unique_ptr<LedTokenParser>
        createLedLdState(std::shared_ptr<IMemory>) const;
    virtual std::unique_ptr<LedTokenParser>
    createLedOutState(std::shared_ptr<const IMemory>) const;
};
}
