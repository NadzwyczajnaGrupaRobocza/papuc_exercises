#include "CollisionDetector.hpp"
#include "sfml_help.hpp"
#include <iostream>

namespace lmg03
{
void CollisionDetector::compute_collisions(
    const sf::Time& tick,
    std::vector<std::unique_ptr<PhysicalEntity>>& entities)
{
    _current_tick = tick;
    for (auto i = 0u; i < entities.size(); ++i)
    {
        for (auto j = i + 1; j < entities.size(); ++j)
        {
            if (collistion_occured_between(*entities[i], *entities[j]))
            {
                recompute_positions(*entities[i], *entities[j]);
            }
        }
    }

    for (auto& e : entities)
    {
        resolve_colistion_with_world_boundry(*e);
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

    const auto e1_pos_on_collision =
        curr_1.position + _last_moved_fraction * displacement_1;
    const auto e2_pos_on_collision =
        curr_2.position + _last_moved_fraction * displacement_2;

    const auto dir_1_to_2 =
        sfml_help::unit(e2_pos_on_collision - e1_pos_on_collision);

    const auto a1 = sfml_help::dot(curr_1.velocity, dir_1_to_2);
    const auto a2 = sfml_help::dot(curr_2.velocity, dir_1_to_2);

    const auto optimizedP =
        (2.0f * (a1 - a2)) / (curr_1.mass + curr_2.mass);

    const auto post_colision_velocity_1 =
        curr_1.velocity - optimizedP * curr_2.mass * dir_1_to_2;
    const auto post_colision_velocity_2 =
        curr_2.velocity + optimizedP * curr_1.mass * dir_1_to_2;

    e1.set_next_state(
        {curr_1.position + _last_moved_fraction * displacement_1,
         post_colision_velocity_1, curr_1.mass});

    e2.set_next_state(
        {curr_2.position + _last_moved_fraction * displacement_2,
         post_colision_velocity_2, curr_2.mass});

    e1.advance_to_next_state();
    e2.advance_to_next_state();

    e1.prepare_next_pos((1.0f - _last_moved_fraction) *
                        _current_tick.asSeconds());
    e2.prepare_next_pos((1.0f - _last_moved_fraction) *
                        _current_tick.asSeconds());
}

void CollisionDetector::resolve_colistion_with_world_boundry(
    PhysicalEntity& e)
{
    // const auto curr = e.get_state();
    const auto next = e.get_next_state();
    const auto r = e.get_radius();

    const auto bound_left = r;
    if (next.position.x < bound_left)
    {
        const auto new_x_pos = 2.0f * bound_left - next.position.x;
        e.set_next_state({{new_x_pos, next.position.y},
                          sfml_help::inv_x(next.velocity),
                          next.mass});
    }

    const auto bound_right = 800.f - r;
    if (next.position.x > bound_right)
    {
        const auto new_x_pos = 2.0f * bound_right - next.position.x;
        e.set_next_state({{new_x_pos, next.position.y},
                          sfml_help::inv_x(next.velocity),
                          next.mass});
    }

    const auto bound_top = r;
    if (next.position.y < bound_top)
    {
        const auto new_y_pos = 2.0f * bound_top - next.position.y;
        e.set_next_state({{next.position.x, new_y_pos},
                          sfml_help::inv_y(next.velocity),
                          next.mass});
    }

    const auto bound_bottom = 600.f - r;
    if (next.position.y > bound_bottom)
    {
        const auto new_y_pos = 2.0f * bound_bottom - next.position.y;
        e.set_next_state({{next.position.x, new_y_pos},
                          sfml_help::inv_y(next.velocity),
                          next.mass});
    }
}
}
