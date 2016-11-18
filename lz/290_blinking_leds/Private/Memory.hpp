#pragma once
#include "IMemory.hpp"
#include "Register.hpp"

namespace lz
{
class Memory : public IMemory
{
public:
    void set_register_a(const Register&) override;
    const Register& get_register_a() const override;

private:
    Register register_a;
};
}
