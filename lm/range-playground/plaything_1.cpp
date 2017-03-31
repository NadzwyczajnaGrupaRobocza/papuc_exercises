#include <iostream>

#include <range/v3/all.hpp>

int main()
{
    const auto NaturalNumberSet = ranges::view::ints(0);
    const auto digits = NaturalNumberSet | ranges::view::take(10);

    const auto print_it = [](const auto num) { std::cout << num << ' '; };

    std::cout << "the digits...\n";
    ranges::for_each(digits, print_it);

    std::cout << "\nthats odd.. very odd...\n";

    ranges::for_each(
        NaturalNumberSet
        | ranges::view::filter([](const auto i) {
            return i % 2 == 1;
        })
        | ranges::view::take(42),
        print_it);

    std::cout << "\nand the prime suspects are...\n";

    const auto prime_number = [](const auto n) {
        if (n < 3)
        {
            return false;
        }
        else
        {
            return ranges::all_of(ranges::view::ints(2, n - 1),
                                  [n](const auto i) { return n % i != 0; });
        }
    };

    ranges::for_each(ranges::view::ints(3)
                     | ranges::view::filter(prime_number)
                     | ranges::view::take(13),
                     print_it);

    std::cout << '\n';
    return 0;
}
