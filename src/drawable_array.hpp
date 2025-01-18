#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include <random>
class DrawableArray : public sf::Drawable, public sf::Transformable {
public:
    DrawableArray(size_t n, sf::Vector2u size, unsigned int padding);
    void randomise();
    void draw(sf::RenderTarget& render_target,
              sf::RenderStates render_states) const;
    size_t len();
    size_t at(size_t i);
    void swap(size_t i, size_t j);

private:
    size_t n;
    std::vector<size_t> vec;
    sf::Vector2u size;
    unsigned int padding;
    std::mt19937 rand_func;
};
