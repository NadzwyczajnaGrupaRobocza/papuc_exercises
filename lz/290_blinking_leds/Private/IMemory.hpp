#pragma once

namespace lz
{
class Register;
class IMemory
{
public:
    virtual ~IMemory() = default;
    virtual void set_register_a(const Register&) = 0;
    virtual const Register& get_register_a() const = 0;
};
}
