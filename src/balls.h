#pragma once
#include <vector>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

struct Balls {
    private:
        std::vector<sf::Vector2f> positions, velocities;
        std::vector<sf::Color> colors;
        std::vector<float> radii;
        sf::Vector2f gravity{sf::Vector2f(0.0, 0.2)};
        uint32_t iterations{6};

    public:
        Balls();
        void spawn_ball(float x, float y);
        void render(sf::RenderWindow& window) const;
        void update(const sf::RenderWindow& window);

    private:
        void apply_vel();
        void collide_boundary(sf::Vector2f center);
        void collide_pair(uint32_t i, uint32_t j);
        void collide_balls();
};
