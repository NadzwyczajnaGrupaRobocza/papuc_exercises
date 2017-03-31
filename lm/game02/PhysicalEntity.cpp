#include "PhysicalEntity.hpp"
#include "HiggsField.hpp"
#include "PhysicalConstants.hpp"
#include "sfml_help.hpp"

using namespace sfml_help;

namespace lmg02
{
PhysicalEntity::PhysicalEntity(common::Log& logInit,
                               const sf::Vector2f& initialPosition,
                               const sf::Vector2f& initialVelocity,
                               float initialMass,
                               const HiggsField& registryInitializer)
    : log{logInit},
      current_state{initialPosition, initialVelocity}, mass{initialMass},
      registry{registryInitializer}
{
}

void PhysicalEntity::prepare_next_pos(float dt)
{
    next_state = compute_next_state(dt);
}

void PhysicalEntity::detect_colision(const sf::FloatRect& ent)
{
    sf::Vector2f size{20.f, 20.f};
    sf::FloatRect this_ent{next_state.position - 0.5f * size, size};
    if (not this_ent.intersects(ent))
    {
        current_state = next_state;
    }
    else
    {
    }
}

sf::Vector2f
PhysicalEntity::gravitational_pull_from(const PhysicalEntity& other) const
{
    const auto& other_pos = other.get_state().position;
    const auto& this_pos = current_state.position;
    auto direction = from_1_to_2_unit(this_pos, other_pos);
    log.info() << "direction:{" << direction.x << ", " << direction.y << "}";

    float numerator =
        static_cast<float>(GRAVITATIONAL_CONSTANT * static_cast<double>(mass) * static_cast<double>(other.mass));
    float denominator = length_squared(other_pos - this_pos);

    return direction * numerator / denominator;
}

void PhysicalEntity::draw(sf::RenderTarget& target)
{
    sf::Vector2f size{20.f, 20.f};
    sf::RectangleShape box{size};
    box.setFillColor(sf::Color::Blue);
    box.setPosition(current_state.position - 0.5f * size);
    target.draw(box);
}

State PhysicalEntity::compute_next_state(float dt)
{
    Derivative a, b, c, d;

    a = evaluate(0.0f, Derivative());
    b = evaluate(dt * 0.5f, a);
    c = evaluate(dt * 0.5f, b);
    d = evaluate(dt, c);

    sf::Vector2f dpos_dt =
        1.0f / 6.0f *
        (a.delta_pos + 2.0f * (b.delta_pos + c.delta_pos) + d.delta_pos);

    sf::Vector2f dv_dt =
        1.0f / 6.0f *
        (a.delta_vee + 2.0f * (b.delta_vee + c.delta_vee) + d.delta_vee);

    return {current_state.position + dpos_dt * dt,
            current_state.velocity + dv_dt * dt};
}

Derivative PhysicalEntity::evaluate(float dt, const Derivative& d)
{
    State state{current_state.position + d.delta_pos * dt,
                current_state.velocity + d.delta_vee * dt};

    return {state.velocity, registry.get_accel(this, dt)};
}
}
