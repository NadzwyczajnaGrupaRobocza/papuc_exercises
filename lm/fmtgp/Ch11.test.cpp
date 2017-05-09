#include "Ch11.hpp"
#include <gtest/gtest.h>

#include <vector>
#include <set>
#include <list>

namespace fmtgp
{

TEST(lm_fmtgp_ch11, givenSingleRangeFrontAndBackSegmentAreSwapped)
{
    std::vector<int> v = {1, 2, 3, 4};
    std::vector<int> v_swapped = {3, 4, 1, 2};

    const auto result = swap_ranges(v.begin(), v.begin() + 2,
                                    v.begin() + 2, v.end());

    ASSERT_EQ(v, v_swapped);
    ASSERT_EQ(result.first, v.begin() + 2);
    ASSERT_EQ(result.second, v.end());
}

TEST(lm_fmtgp_ch11, givenTwoDifferentContainersWillSwapTheirContent)
{
    std::list<int> s = {1, 2, 3};
    std::vector<int> v = {6, 7, 8};

    const auto result = swap_ranges(s.begin(), s.end(),
                                    v.begin(), v.end());
    (void)result;

    std::list<int> s_swapped = {6, 7, 8};
    std::vector<int> v_swapped = {1, 2, 3};
    ASSERT_EQ(v, v_swapped);
    ASSERT_EQ(s, s_swapped);
}

TEST(lm_fmtgp_ch11, givenNonEmptyRangeWillRotateWithFwdIterAlgorithm)
{
    std::list<int> l = {1, 2, 3, 4, 5, 6, 7};
    std::list<int> l_rotated = {3, 4, 5, 6, 7, 1, 2};
    auto mid = std::find(l.begin(), l.end(), 3);

    auto n_mid = fmtgp::rotate(l.begin(), mid, l.end());

    ASSERT_EQ(l, l_rotated);
    ASSERT_EQ(*n_mid, 1);
    ASSERT_EQ(*std::next(n_mid), 2);
    ASSERT_EQ(*std::prev(n_mid), 7);
    ASSERT_EQ(std::distance(l.begin(), n_mid), 5);


}

TEST(lm_fmtgp_ch11, willRotateRandomAccessRange)
{
    std::vector<int> l = {1, 2, 3, 4, 5, 6, 7};
    std::vector<int> l_rotated = {3, 4, 5, 6, 7, 1, 2};

    auto mid = std::find(l.begin(), l.end(), 3);

    auto n_mid = fmtgp::rotate(l.begin(), mid, l.end(),
                               std::random_access_iterator_tag{});
    (void)n_mid;
    ASSERT_EQ(l, l_rotated);
}
}
