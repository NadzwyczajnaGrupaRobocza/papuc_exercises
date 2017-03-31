#include "InstructionBuilderCombinator.hpp"
#include "Processor.hpp"
#include "throw_assert.hpp"
#include <bitset>
#include <fstream>

int main(int argc, char** argv)
{
    throw_assert(argc >= 2, "not enough arguments");

    std::string inputFileName{argv[1]};
    std::ifstream inputFile{inputFileName};
    ltm::InstructionBuilderCombinator ibc;
    auto led = [](ltm::u8_t v) {
        std::cout << std::bitset<8>(v).to_string('.', '*') << '\n';
    };
    ltm::Processor proc{{{ltm::Register::out_0, led}}};
    return proc.runProgram(ibc.process(inputFile));
}
