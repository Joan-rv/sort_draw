#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <array>
#include <cstddef>
#include <random>
#include <stdexcept>
template <size_t N>
class DrawableArray : public sf::Drawable, public sf::Transformable {
public:
    DrawableArray(sf::Vector2u size, unsigned int padding);
    void randomise();
    void draw(sf::RenderTarget& render_target,
              sf::RenderStates render_states) const;

private:
    std::array<size_t, N> arr;
    sf::Vector2u size;
    unsigned int padding;
    std::mt19937 rand_func;
};

template <size_t N>
DrawableArray<N>::DrawableArray(sf::Vector2u size, unsigned int padding)
    : size(size), padding(padding), rand_func(std::random_device()()) {
    if (size.x % N != 0 || size.x / N <= padding || size.y % N != 0 ||
        size.y / N < 1) {
        throw std::invalid_argument(
            "Invalid combination of size, padding, and N. The "
            "following conditions must hold: "
            "size.x % N == 0, size.x / N > padding, size.y % N == 0,and "
            "size.y / N >= 1");
    }
    for (size_t i = 0; i < N; i++) {
        arr[i] = i + 1;
    }
    randomise();
}

template <size_t N> void DrawableArray<N>::randomise() {
    std::shuffle(arr.begin(), arr.end(), rand_func);
}

template <size_t N>
void DrawableArray<N>::draw(sf::RenderTarget& target,
                            sf::RenderStates states) const {
    states.transform.combine(getTransform());
    unsigned int rect_width = size.x / N;
    unsigned int rect_height = size.y / N;
    for (size_t i = 0; i < N; i++) {
        sf::RectangleShape rect(
            sf::Vector2f(rect_width - padding, rect_height * arr[i]));
        rect.setPosition(
            sf::Vector2f(padding + rect_width * i, rect_height * (N - arr[i])));
        target.draw(rect, states);
    }
}
