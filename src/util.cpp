#include <cstdint>
#include <util.h>
#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

sf::Color random_color() {
    const uint32_t color = Random::get(0x0, 0xFFFFFF);
    uint8_t r = color >> 16 & 0xFF;
    uint8_t g = color >> 8 & 0xFF;
    uint8_t b = color >> 0 & 0xFF;

    return {r, g, b};
}

sf::Vector2f center_of_screen(const sf::RenderWindow &window) {
    const sf::Vector2u size = window.getSize();
    const auto size_f = static_cast<sf::Vector2f>(size);
    return { size_f.x / 2.0f, size_f.y / 2.0f };
}

float distance_squared(const sf::Vector2f a, const sf::Vector2f b) {
    const auto dx = a.x - b.x;
    const auto dy = a.y - b.y;

    return dx*dx + dy*dy;
}

float distance(const sf::Vector2f a, const sf::Vector2f b) {
    return sqrt(distance_squared(a, b));
}

float vec_len(const sf::Vector2f a) {
    return sqrt(a.x * a.x + a.y * a.y);
}

sf::Vector2f vec_normalize(sf::Vector2f a) {
    return a / vec_len(a);
}
