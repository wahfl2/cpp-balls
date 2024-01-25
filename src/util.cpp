#include <cstdint>
#include <util.h>
#include <effolkronium/random.hpp>
#include <glm/vec2.hpp>

using Random = effolkronium::random_static;

sf::Color random_color() {
    const uint32_t color = Random::get(0x0, 0xFFFFFF);
    uint8_t r = color >> 16 & 0xFF;
    uint8_t g = color >> 8 & 0xFF;
    uint8_t b = color >> 0 & 0xFF;

    return {r, g, b};
}

glm::vec2 center_of_screen(const sf::RenderWindow &window) {
    const sf::Vector2u size = window.getSize();
    const auto size_f = static_cast<sf::Vector2f>(size);
    return { size_f.x / 2.0f, size_f.y / 2.0f };
}

sf::Vector2f glm2sf(glm::vec2 v) {
    return {v.x, v.y};
}

glm::vec2 sf2glm(sf::Vector2f v) {
    return {v.x, v.y};
}