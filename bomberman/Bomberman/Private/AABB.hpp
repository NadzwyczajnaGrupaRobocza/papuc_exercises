#pragma once

#include <type_traits>

namespace bomberman
{
class Entity;
struct AABB
{
    float x_coord;
    float y_coord;
    float width;
    float height;

    Entity* entity;
};
static_assert(std::is_pod<AABB>::value, "AABB must be a POD type.");
}
