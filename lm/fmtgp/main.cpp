#include <iostream>
#include "ch04.hpp"

int main(int argc, char *argv[])
{
    std::cout << "Hello Mathematics and Generic Programming!" << std::endl;
    std::cout << "quotient test1: " << (quotient(5.0, 2.0) == 2 ? "pass" : "fail") << '\n';
    std::cout << "quotient_remainder test1: " << (quotient_remainder(8.3, 3.0) == std::make_pair(2, 2.3) ? "pass" : "fail") << "\n";
    const auto res = quotient_remainder(8.3, 3.0);
    std::cout << "quotient_remainder test1a: " << (res.first == 2) << '\n';
    std::cout << "quotient_remainder test1b: " << (res.second )
    std::cout << "f:" << res.first << " s:" << res.second << "\n";
    return 0;
}
