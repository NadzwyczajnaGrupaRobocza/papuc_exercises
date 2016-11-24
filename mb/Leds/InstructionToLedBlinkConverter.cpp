#include "InstructionToLedBlinkConverter.hpp"

#include <bitset>
#include <iostream>
#include <sstream>
#include <algorithm>


InstructionToLedBlinkConverter::InstructionToLedBlinkConverter()
    : instructionPrefix{"ld a,"},
      instructionPrefixLength{ static_cast<uint>( instructionPrefix.length() ) }
{}

void InstructionToLedBlinkConverter::convert(std::string& line)
{
    convertInstructionToValue(line);
    convertLineToLedSequence(line);
}

void InstructionToLedBlinkConverter::convertInstructionToValue(std::string& line)
{
    if( line.find(instructionPrefix) != std::string::npos )
    {
        line = line.substr( instructionPrefixLength );
    }
    else
    {
        std::cout << "Wrong instrunction format" << std::endl;
        //throw
    }
}

void InstructionToLedBlinkConverter::convertLineToLedSequence(std::string& line)
{
    const uint value = static_cast<uint>( std::stoi(line) );
    line = std::bitset<8>(value).to_string('.', '*');
}
