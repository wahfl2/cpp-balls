#include <vector>
#include <balls.h>
#include <util.h>
#include <effolkronium/random.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <glm/glm.hpp>

using Random = effolkronium::random_static;

constexpr glm::vec2 DAMPING = glm::vec2(0.9995);

Balls::Balls() = default;

void Balls::spawn_ball(float x, float y) {
    positions.emplace_back(x, y);
    velocities.emplace_back(0.0, 0.0);
    colors.push_back(random_color());
    radii.push_back(Random::get(5, 10));
}

void Balls::render(sf::RenderWindow& window) const {
    for (uint32_t i = 0; i < positions.size(); ++i) {
        const auto radius = radii[i];
        const auto pos = positions[i];
        const auto color = colors[i];

        auto circle = sf::CircleShape(radius, 30);
        circle.setPosition(glm2sf(pos - glm::vec2(radius)));
        circle.setFillColor(color);

        window.draw(circle);
    }
}

void Balls::update(const sf::RenderWindow& window) {
    this->apply_gravity();

    for (int i = 0; i < substeps; ++i) {
        this->apply_vel(substeps);
        for (int j = 0; j < this->iterations; ++j) {
            this->collide_balls();
            this->collide_boundary(center_of_screen(window));
        }
    }
}

void Balls::apply_gravity() {
    for (uint32_t i = 0; i < positions.size(); ++i) {
        glm::vec2& vel = velocities[i];

        vel += gravity;
        vel *= DAMPING;
    }
}


void Balls::apply_vel(const uint32_t substeps) {
    const float mul = 1.0f / substeps;
    for (uint32_t i = 0; i < positions.size(); ++i) {
        positions[i] += velocities[i] * mul;
    }
}

void Balls::collide_boundary(const glm::vec2 center) {
    for (uint32_t i = 0; i < positions.size(); ++i) {
        const auto pos = positions[i];
        const auto radius = radii[i];

        const auto dist = glm::distance(pos, center);
        const float allowed_dist = 400.0f - radius;

        if (dist > allowed_dist) {
            const auto move_dist = dist - allowed_dist;
            const auto resolution_vec = normalize(pos - center) * move_dist;

            positions[i] -= resolution_vec;
            velocities[i] -= resolution_vec;
        }
    }
}

void Balls::collide_pair(const uint32_t i, const uint32_t j) {
    if (i == j) return;

    auto& b1_pos = positions[i];
    auto& b2_pos = positions[j];
    const auto b1_rad = radii[i];
    const auto b2_rad = radii[j];

    auto added_radii = b1_rad + b2_rad;
    if (abs(b1_pos.x - b2_pos.x) >= added_radii) return;
    if (abs(b1_pos.y - b2_pos.y) >= added_radii) return;

    const auto dist = distance(b1_pos, b2_pos);
    if (dist > added_radii) return;

    const auto move_dist = added_radii - dist;
    const auto resolution_vec = normalize(b1_pos - b2_pos) * (move_dist * 0.5f);

    b1_pos += resolution_vec;
    b2_pos -= resolution_vec;

    velocities[i] += resolution_vec;
    velocities[j] -= resolution_vec;
}

void Balls::collide_balls() {
    for (int i = 0; i < positions.size(); ++i) {
        for (int j = i; j < positions.size(); ++j) {
            this->collide_pair(i, j);
        }
    }
}
