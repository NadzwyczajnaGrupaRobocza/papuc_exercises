#pragma once
#include <algorithm>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <map>
#include <vector>

namespace MMM
{
template <typename T>
class Properties
{
  public:
    Properties(std::vector<T>);
    T getMin() const;
    T getMax() const;
    std::set<T> getMode() const;

  private:
    using FreqMap = std::map<T, unsigned int>;
    std::vector<T> data;
    FreqMap freq;
};

template <typename T>
Properties<T>::Properties(std::vector<T> dataInitializer)
    : data{dataInitializer}, freq{}
{
    boost::for_each(data,
                  [this](const T &item) { freq[item]++; });
}

template <typename T>
T Properties<T>::getMin() const
{
    return freq.begin()->first;
}

template <typename T>
T Properties<T>::getMax() const
{
    return freq.rbegin()->first;
}

template <typename T>
std::set<T> Properties<T>::getMode() const
{
    using FreqEl = typename FreqMap::value_type;
    auto freqCmp = [](const FreqEl &lhs, const FreqEl &rhs) {
        return lhs.second < rhs.second;
    };
    auto maxElement = boost::max_element(freq, freqCmp);

    auto keepEqualToMax = [&](const FreqEl &el) {
        return el.second == maxElement->second;
    };

    using namespace boost::adaptors;
    std::set<T> modes;
    boost::copy(freq | filtered(keepEqualToMax) | map_keys,
                std::inserter(modes, modes.end()));
    return modes;
}
}
