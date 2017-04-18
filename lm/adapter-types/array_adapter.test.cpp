#include "array_adapter.hpp"
#include "gtest/gtest.h"

#include <algorithm>
#include <iostream>
#include <range/v3/all.hpp>
#include <vector>

namespace accs
{
TEST(lm_array_adapter, willAllowReadingFromExistingArray)
{
    int stuff[] = {1, 3, 4, 10, -13};
    std::vector<int> t = {};
    std::vector<int> expected_t = {1, 3, 4, 10, -13};

    // array_access<int> stuff_a{stuff, 5};
    auto stuff_a = adapt_array(stuff);

    std::copy(stuff_a.begin(), stuff_a.end(), std::back_inserter(t));

    ASSERT_EQ(t, expected_t);
}

TEST(lm_array_adapter, willAllowWritingIntoArray)
{
    constexpr std::size_t N = 10;
    float stuff[N];

    std::vector<float> source = {1.1, 1.3, 3.10, -11.123, 88.1, 7.3, 5.44};

    auto stuff_a = adapt_array(stuff);

    std::copy(source.begin(), source.end(), stuff_a.begin());

    ASSERT_TRUE(std::equal(source.begin(), source.end(), stuff_a.begin()));
}

TEST(lm_array_adapter, willWorkWithRangeForLoop)
{
    int stuff[] = {1, 2, 3};
    std::vector<int> res = {};

    auto stuff_a = adapt_array(stuff);

    for (const auto& el : stuff_a)
    {
        res.push_back(el);
    }

    ASSERT_EQ(res.size(), 3ull);
    ASSERT_TRUE(std::equal(res.begin(), res.end(), stuff));
}

TEST(lm_array_adapter, willWorkWithConstArray)
{
    const int stuff[] = {1, 2, 3};
    std::vector<int> res = {};

    auto stuff_a = adapt_array(stuff);

    std::for_each(stuff_a.begin(), stuff_a.end(),
                  [&](const auto& el) { res.push_back(el); });

    ASSERT_EQ(res.size(), 3ull);
}

TEST(lm_array_adapter, willWorkWithRangeV3)
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> out{};
    std::vector<int> odds = {1, 3, 5, 7, 9};
    auto acc = adapt_array(a);

    const auto is_odd = [](const auto n) {
        return static_cast<bool>(n & 0x1);
    };

    ranges::for_each(acc | ranges::view::filter(is_odd),
                     [&](const auto& el) { out.push_back(el); });

    ASSERT_EQ(out, odds);
}

TEST(lm_array_adapter, willWorkForDynamicArrays)
{
    char* a = new char[20];
    auto acc = adapt_array<20>(a);
    std::fill(acc.begin(), acc.end(), 'z');

    std::string in = "abcdefghijk";
    std::copy(in.begin(), in.end(), a);
    const std::string expected = "abcdefghijkzzzzzzzzz";

    ASSERT_TRUE(std::equal(expected.begin(), expected.end(), acc.begin()));

    delete[] a;
}

TEST(lm_array_adapter, willWorkForConstDynamicArrays)
{
    char src = 'z';
    char* a = new char[20];
    auto acc = adapt_array<20>(a);
    std::generate(acc.begin(), acc.end(), [&]() { return src--; });

    const char* c_a = a;
    auto c_acc = adapt_array<10>(c_a);
    const std::string expected = "zyxwvutsrq";
    ASSERT_TRUE(
        std::equal(expected.begin(), expected.end(), c_acc.begin()));

    delete[] a;
}

TEST(lm_array_adapter, WillProvideViewSemanticWhenConst)
{
    char s[] = "abcd";
    const auto adptr = adapt_array(s);
    auto iter_b = adptr.begin();
    auto iter_e = adptr.end();

    static_assert(std::is_same<typename decltype(adptr)::const_iterator,
                               decltype(iter_b)>::value,
                  "iterator should be const for const adapter");
    static_assert(std::is_same<typename decltype(adptr)::const_iterator,
                               decltype(iter_e)>::value,
                  "iterator should be const for const adapter");
    ASSERT_EQ(adptr.size(), 5ull);
}

TEST(lm_array_adapter, willIterateInReverse)
{
    const int ar[] = {1, 2, 3};
    const auto adp = adapt_array(ar);
    const std::vector<int> expected_out = {3, 2, 1};

    std::vector<int> out;
    auto iter_crb = adp.rbegin();
    auto iter_cre = adp.rend();
    static_assert(
        std::is_same<typename decltype(adp)::const_reverse_iterator,
                     decltype(iter_crb)>::value,
        "iterator should be const for const adapter");
    static_assert(
        std::is_same<typename decltype(adp)::const_reverse_iterator,
                     decltype(iter_cre)>::value,
        "iterator should be const for const adapter");
    std::copy(iter_crb, iter_cre, std::back_inserter(out));

    ASSERT_EQ(out, expected_out);
}

TEST(lm_array_adapter, willFunctionAsReverseOutputIterator)
{
    int ar[5];
    auto adp = adapt_array(ar);
    std::vector<int> input = {1, 2, 3, 4, 5};
    std::vector<int> expected_result = {5, 4, 3, 2, 1};

    std::copy(input.begin(), input.end(), adp.rbegin());

    ASSERT_TRUE(
        std::equal(expected_result.begin(), expected_result.end(), ar));
}

TEST(vector_probe, willCompileForConstVectorBeginEndCalls)
{
    const std::vector<int> t = {1, 2, 3};
    auto it = t.begin();

    static_assert(
        std::is_same<decltype(it), std::vector<int>::const_iterator>::value,
        "should work");

    (void)it;
}
}
