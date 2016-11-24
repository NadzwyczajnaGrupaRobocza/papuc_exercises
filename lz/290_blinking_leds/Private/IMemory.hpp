#pragma once

namespace lz
{
class Byte;
class IMemory
{
public:
    virtual ~IMemory() = default;
    virtual void set_register_a(const Byte&) = 0;
    virtual const Byte& get_register_a() const = 0;
};
}
