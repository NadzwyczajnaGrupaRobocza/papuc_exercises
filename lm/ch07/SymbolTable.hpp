#pragma once
#include "Optional.hpp"

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
