#pragma once
#include "IMemory.hpp"
#include "Byte.hpp"

namespace lz
{
class Memory : public IMemory
{
public:
    void set_register_a(const Byte&) override;
    const Byte& get_register_a() const override;

private:
    Byte register_a;
};
}
