#include "LedSimulation.hpp"

#include <boost/range/algorithm/for_each.hpp>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

#include "LedSimulationFsm.hpp"

namespace lz
{
LedSimulation::LedSimulation(
    std::unique_ptr<ILedSimulationFsm> ledSimulationFsm)
    : fsm{std::move(ledSimulationFsm)}
{
}

void LedSimulation::readCommands(std::istream& input)
{
    tokens.clear();
    input >> std::noskipws;
    std::istream_iterator<char> it(input);
    std::string sentence(it, std::istream_iterator<char>{});
    std::istringstream iss(sentence);
    // std::copy(std::istream_iterator<std::string>{iss},
    //           std::istream_iterator<std::string>{}, std::back_inserter(tokens));

    std::transform(
        std::istream_iterator<std::string>{iss},
        std::istream_iterator<std::string>{}, std::back_inserter(tokens),
        [](auto&& str_token) { return LedToken{std::move(str_token)}; });
}

void LedSimulation::run()
{
    boost::range::for_each(tokens,
                           [this](const auto& token) { fsm->parse(token); });
}

void LedSimulation::printCommandTokens(std::ostream& output) const
{
    boost::range::for_each(
        tokens, [&output](const auto& token) { output << token << std::endl; });
}
}
