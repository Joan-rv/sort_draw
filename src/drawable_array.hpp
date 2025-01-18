#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <chrono>
#include <cstddef>
#include <mutex>
#include <random>
class DrawableArray : public sf::Drawable, public sf::Transformable {
public:
    DrawableArray(size_t n, sf::Vector2u size, unsigned int padding,
                  std::chrono::nanoseconds delay);
    void randomise();
    void draw(sf::RenderTarget& render_target,
              sf::RenderStates render_states) const;
    size_t len();
    size_t at(size_t i);
    void write(size_t i, size_t val);
    void swap(size_t i, size_t j);

private:
    const size_t n;
    std::vector<size_t> vec;
    mutable std::mutex vec_mutex;
    const sf::Vector2u size;
    const unsigned int padding;
    std::mt19937 rand_func;
    const std::chrono::nanoseconds delay;
};
