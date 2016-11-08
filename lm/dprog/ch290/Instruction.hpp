#pragma once

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
    return lhs.operation == rhs.operation and
        lhs.reg == rhs.reg and
        lhs.value == rhs.value;
}

enum class OperationType : u8_t
{
    INVALID = 0,
    load,
    output
};

enum class Register : u8_t
{
    INVALID = 0,
    out_0,
    reg_a
};
