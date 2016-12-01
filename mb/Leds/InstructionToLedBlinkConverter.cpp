#include "InstructionToLedBlinkConverter.hpp"

#include <bitset>
//#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdexcept>


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
    if( line.substr( 0, instructionPrefixLength ) == instructionPrefix )
    {
        line = line.substr( instructionPrefixLength );
    }
    else
    {
        throw std::invalid_argument{"Wrong instruction: " + line};
    }
}

void InstructionToLedBlinkConverter::convertLineToLedSequence(std::string& line)
{
    const uint value = static_cast<uint>( std::stoi(line) );
    if (value < 256)
    {
        line = std::bitset<8>(value).to_string('.', '*');
    }
    else
    {
        throw std::out_of_range{"To high value"};
    }
}
