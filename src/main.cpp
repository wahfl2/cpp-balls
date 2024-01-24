#include <balls.h>
#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window {
        { 1600u, 900u },
        "balls"
    };

    window.setFramerateLimit(60);

    auto balls = Balls();

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            switch (event.type) {
                case sf::Event::Closed: {
                    window.close();
                }

                default:;
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i position = sf::Mouse::getPosition(window);
            balls.spawn_ball(position.x, position.y);
        }

        window.clear();

        balls.update(window);
        balls.render(window);

        window.display();
    }
}