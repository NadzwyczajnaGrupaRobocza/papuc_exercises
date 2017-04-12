#include "Ch11.hpp"
#include <gtest/gtest.h>

#include <vector>
#include <set>
#include <list>

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
