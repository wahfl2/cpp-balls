#pragma once
#include <cstdint>
#include <glm/vec2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

sf::Color random_color();

glm::vec2 center_of_screen(const sf::RenderWindow& window);

sf::Vector2f glm2sf(glm::vec2 v);
glm::vec2 sf2glm(sf::Vector2f v);