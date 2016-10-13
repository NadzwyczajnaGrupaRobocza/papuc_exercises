#pragma once
#include <experimental/optional>

template <typename T>
using Optional = std::experimental::optional<T>;

namespace calc
{
class SymbolTable
{
public:
    virtual ~SymbolTable() = default;
    Optional<double> getValue(const std::string&);
    void storeValue(const std::string&, double);
};
}
