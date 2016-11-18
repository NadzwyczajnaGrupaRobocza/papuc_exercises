#pragma once
#include <gmock/gmock.h>

#include "IMemory.hpp"

namespace lz
{
class MemoryMock : public IMemory
{
public:
    MOCK_METHOD1(set_register_a, void(const Register&));
    MOCK_CONST_METHOD0(get_register_a, const Register&());
};
}
