#pragma once
#include <vector>
#include <glm/vec2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

struct Balls {
    private:
        std::vector<glm::vec2> positions, velocities;
        std::vector<sf::Color> colors;
        std::vector<float> radii;
        glm::vec2 gravity{ glm::vec2(0.0, 0.2) };
        uint32_t iterations{ 6 }, substeps{ 1 };

    public:
        Balls();
        void spawn_ball(float x, float y);
        void render(sf::RenderWindow& window) const;
        void update(const sf::RenderWindow& window);

    private:
        void apply_gravity();
        void apply_vel(uint32_t substeps);
        void collide_boundary(glm::vec2 center);
        void collide_pair(uint32_t i, uint32_t j);
        void collide_balls();
};
