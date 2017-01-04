#pragma once

#include <type_traits>

#include "fp_manip.hpp"

namespace physics
{
struct AABB
{
    float x;
    float y;
    float width;
    float height;

    static inline AABB create(float x, float y, float width, float height)
    {
        AABB aabb;
        aabb.x = x;
        aabb.y = y;
        aabb.width = width;
        aabb.height = height;
        return aabb;
    }
};

static_assert(std::is_pod<AABB>::value, "AABB must be a POD type.");

inline bool operator==(const AABB& lhs, const AABB& rhs)
{
    return fp::equal(lhs.x, rhs.x) && fp::equal(lhs.y, rhs.y) &&
           fp::equal(lhs.width, rhs.width) && fp::equal(lhs.height, rhs.height);
}

inline bool operator!=(const AABB& lhs, const AABB& rhs)
{
    return not(lhs == rhs);
}
}
