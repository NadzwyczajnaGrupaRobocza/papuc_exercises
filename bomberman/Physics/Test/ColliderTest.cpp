#include <gtest/gtest.h>

#include "AABB.hpp"
#include "Collider.hpp"

using namespace ::testing;

namespace physics
{
class ColliderTest : public ::Test
{
public:
};

TEST_F(ColliderTest, createCollider)
{
    auto aabb = AABB::create(0, 0, 10, 10);
    Collider collider{aabb};
    EXPECT_TRUE(aabb == collider.get_aabb());
    EXPECT_FALSE(aabb == Collider{AABB::create(0, 1, 20, 30)}.get_aabb());
}
}
