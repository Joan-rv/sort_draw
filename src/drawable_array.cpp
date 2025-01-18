#include <algorithm>
#include <drawable_array.hpp>
#include <stdexcept>
DrawableArray::DrawableArray(size_t n, sf::Vector2u size, unsigned int padding)
    : n(n), size(size), padding(padding), rand_func(std::random_device()()) {
    if (size.x % n != 0 || size.x / n <= padding || size.y % n != 0 ||
        size.y / n < 1) {
        throw std::invalid_argument(
            "Invalid combination of size, padding, and N. The "
            "following conditions must hold: "
            "size.x % N == 0, size.x / N > padding, size.y % N == 0,and "
            "size.y / N >= 1");
    }
    vec.reserve(n);
    for (size_t i = 0; i < n; i++) {
        vec.push_back(i + 1);
    }
    randomise();
}

void DrawableArray::randomise() {
    std::shuffle(vec.begin(), vec.end(), rand_func);
}

size_t DrawableArray::len() { return n; }

size_t DrawableArray::at(size_t i) { return vec[i]; }

void DrawableArray::swap(size_t i, size_t j) { std::swap(vec[i], vec[j]); }

void DrawableArray::draw(sf::RenderTarget& target,
                         sf::RenderStates states) const {
    states.transform.combine(getTransform());
    unsigned int rect_width = size.x / n;
    unsigned int rect_height = size.y / n;
    for (size_t i = 0; i < n; i++) {
        sf::RectangleShape rect(
            sf::Vector2f(rect_width - padding, rect_height * vec[i]));
        rect.setPosition(
            sf::Vector2f(padding + rect_width * i, rect_height * (n - vec[i])));
        target.draw(rect, states);
    }
}
