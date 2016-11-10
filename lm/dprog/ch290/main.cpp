#include "InstructionLexer.hpp"
#include "Processor.hpp"
#include "throw_assert.hpp"
#include <bitset>
#include <fstream>

int main(int argc, char** argv)
{
    throw_assert(argc >= 1, "not enough arguments");

    std::string inputFileName{argv[1]};
    std::ifstream inputFile{inputFileName};
    InstructionLexer lexer;
    auto led = [](u8_t v) {
        std::cout << std::bitset<8>(v).to_string('.', '*') << '\n';
    };
    Processor proc{{{Register::out_0, led}}};
    return proc.runProgram(lexer.lex(inputFile));
}
