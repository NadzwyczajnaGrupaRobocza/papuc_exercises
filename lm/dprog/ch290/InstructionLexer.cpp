#include "InstructionLexer.hpp"
#include <iostream>
#include <istream>

Instruction buildLoadInstruction(const std::smatch& m)
{
    if (m.size() != 3)
    {
        for (auto i = 0u; i < m.size(); ++i)
        {
            std::cout << "m[" << i << "]=" << m[i] << '\n';
        }
        throw std::logic_error("epic fail");
    }

    const std::string registryName = m[1];
    const std::string valueStr = m[2];

    Register reg;

    if ((registryName.size() == 1 and registryName[0] == 'a'))
    {
        reg = Register::reg_a;
    }
    else
    {
        throw std::logic_error("addressing unknown register");
    }

    int value = std::stoi(valueStr);

    if (not(value >= std::numeric_limits<u8_t>::lowest() and
            value <= std::numeric_limits<u8_t>::max()))
    {
        throw std::logic_error("invalid value in op");
    }

    return {OperationType::load, reg, static_cast<u8_t>(value),
            Register::INVALID};
}

Instruction buildOutputInstruction(const std::smatch& m)
{
    if (m.size() != 3)
    {
        for (auto i = 0u; i < m.size(); ++i)
        {
            std::cout << "m[" << i << "]=" << m[i] << '\n';
        }
        throw std::logic_error("epic fail");
    }

    const Register outReg = [](const std::string& regStr) {
        if ((regStr.size() == 1u) and regStr[0] == '0')
        {
            return Register::out_0;
        }
        throw std::logic_error("invalid output register");
    }(m[1]);

    const Register srcReg = [](const std::string& regStr) {
        if ((regStr.size() == 1u) and regStr[0] == 'a')
        {
            return Register::reg_a;
        }
        throw std::logic_error("invalid source register");
    }(m[2]);

    return {OperationType::output, outReg, 0u, srcReg};
}

InstructionLexer::InstructionLexer()
    : knownInstructions{
          {std::regex("\\s+ld ([a-z]),(\\d+)"), &buildLoadInstruction},
          {std::regex("\\s+out \\((\\d)\\),([a-z])"), &buildOutputInstruction}}
{
}

std::vector<Instruction> InstructionLexer::lex(std::istream& in)
{
    std::vector<Instruction> iv;
    for (std::string line; std::getline(in, line);)
    {
        if (shouldProcessLine(line))
        {
            iv.push_back(processSingleInstruction(line));
        }
    }

    return iv;
}

bool InstructionLexer::shouldProcessLine(const std::string& line)
{
    return not std::regex_match(line, std::regex("\\s*"));
}

Instruction
InstructionLexer::processSingleInstruction(const std::string& instruction)
{
    std::smatch m;
    for (const auto& pbRel : knownInstructions)
    {
        if (std::regex_match(instruction, m, pbRel.first))
        {
            return pbRel.second(m);
        }
    }

    throw std::logic_error("epic double fail");
}
