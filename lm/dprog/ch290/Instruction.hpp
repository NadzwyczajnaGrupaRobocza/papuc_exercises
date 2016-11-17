#pragma once

#include <string>

using u8_t = unsigned char;
static_assert(sizeof(u8_t) == 1, "epic fail");

enum class OperationType : u8_t;
enum class Register : u8_t;

struct Instruction
{
    OperationType operation;
    Register reg;
    u8_t value;
    Register srcReg;
};

inline bool operator==(const Instruction& lhs, const Instruction& rhs)
{
    return lhs.operation == rhs.operation and lhs.reg == rhs.reg and
           lhs.value == rhs.value and lhs.srcReg == rhs.srcReg;
}

enum class OperationType : u8_t
{
    INVALID = 0,
    load,
    output,
    rotateLeftCyclic,
    rotateRightCyclic,
    decrementAndJump
};

enum class Register : u8_t
{
    INVALID = 0,
    out_0,
    reg_a,
    reg_b
};

inline bool isValidInternalRegisterName(const std::string& name)
{
    return (name.size() == 1 and
            (name[0] == 'a' or name[0] == 'b'));
}

inline bool isValidOutputRegisterName(const std::string& name)
{
    return (name.size() == 1 and
            (name[0] == '0'));
}

inline bool isOutputRegister(Register r)
{
    return (r == Register::out_0);
}

inline bool isInternalRegister(Register r)
{
    return (r == Register::reg_a) or (r == Register::reg_b);
}

inline Register registerNameToEnum(const std::string& name)
{
    if (name == "a")
    {
        return Register::reg_a;
    }
    else if (name == "b")
    {
        return Register::reg_b;
    }
    else if (name == "0")
    {
        return Register::out_0;
    }
    else
    {
        return Register::INVALID;
    }
}
