#pragma once
#include <cstdint>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

sf::Color random_color();

sf::Vector2f center_of_screen(const sf::RenderWindow& window);

float distance_squared(sf::Vector2f a, sf::Vector2f b);
float distance(sf::Vector2f a, sf::Vector2f b);

float vec_len(sf::Vector2f a);
sf::Vector2f vec_normalize(sf::Vector2f a);