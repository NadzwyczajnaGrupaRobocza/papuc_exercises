#include "CollisionDetector.hpp"
#include "sfml_help.hpp"
#include <iostream>

namespace lmg03
{
void CollisionDetector::compute_collisions(
    std::vector<PhysicalEntity>& entities)
{
    for (auto& e1 : entities)
    {
        for (auto& e2 : entities)
        {
            if (&e1 == &e2)
            {
                continue;
            }

            if (collistion_occured_between(e1, e2))
            {
                recompute_positions(e1, e2);
            }
        }
    }
}

bool CollisionDetector::collistion_occured_between(const PhysicalEntity& e1,
                                                   const PhysicalEntity& e2)
{
    const auto curr_1 = e1.get_state();
    const auto curr_2 = e2.get_state();
    const auto next_1 = e1.get_next_state();
    const auto next_2 = e2.get_next_state();

    const auto displacement_1 = next_1.position - curr_1.position;
    const auto displacement_2 = next_2.position - curr_2.position;

    const auto displacement = displacement_1 - displacement_2;

    const auto r1 = e1.get_radius();
    const auto r2 = e2.get_radius();

    const auto from_1_to_2 = curr_2.position - curr_1.position;

    if (sfml_help::dot(from_1_to_2, displacement_1) < 0)
    {
        // we're moving away from 2
        return false;
    }

    if (sfml_help::dist(next_1.position, next_2.position) > r1 + r2)
    {
        return false;
    }

    const auto unit_dis = sfml_help::unit(displacement);
    // cl is s.t. unit(displacement) * cl is closest point to e2 on
    // displacement line
    const auto cl = sfml_help::dot(unit_dis, from_1_to_2);

    const auto d0_sqr = sfml_help::length_squared(from_1_to_2) - cl * cl;

    const auto d1_sqr = (r1 + r2) * (r1 + r2) - d0_sqr;
    const auto d1 = std::sqrt(d1_sqr);

    const auto dist_moved_before_touch = cl - d1;

    const auto displacement_length = sfml_help::length(displacement);

    if (displacement_length < dist_moved_before_touch)
    {
        return false;
    }

    _last_moved_fraction = dist_moved_before_touch / displacement_length;

    return true;
}

void CollisionDetector::recompute_positions(PhysicalEntity& e1,
                                            PhysicalEntity& e2)
{
    const auto curr_1 = e1.get_state();
    const auto curr_2 = e2.get_state();
    const auto next_1 = e1.get_next_state();
    const auto next_2 = e2.get_next_state();

    const auto displacement_1 = next_1.position - curr_1.position;
    const auto displacement_2 = next_2.position - curr_2.position;

    const auto e1_pos_on_collision = curr_1.position + _last_moved_fraction * displacement_1;
    const auto e2_pos_on_collision = curr_2.position + _last_moved_fraction * displacement_2;

    const auto dir_1_to_2 = sfml_help::unit(e2_pos_on_collision - e1_pos_on_collision);

    const auto post_colision_velocity_1 = sfml_help::invert_parallel_component(curr_1.velocity, dir_1_to_2);
    const auto post_colision_velocity_2 = sfml_help::invert_parallel_component(curr_2.velocity, dir_1_to_2);

    e1.set_next_state(
        {curr_1.position + _last_moved_fraction * displacement_1,
         post_colision_velocity_1,
         curr_1.mass});

    e2.set_next_state(
        {curr_2.position + _last_moved_fraction * displacement_2,
         post_colision_velocity_2,
         curr_2.mass});
}


}
