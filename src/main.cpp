#include <SFML/Graphics.hpp>
#include <drawable_array.hpp>
#include <functional>
#include <sorts.hpp>
#include <thread>

int main() {
    sf::RenderWindow window(sf::VideoMode({1002, 600}), "sort_draw");
    DrawableArray drawable_array(200, {1000, 400}, 2,
                                 std::chrono::milliseconds(1));
    drawable_array.setPosition({0, 200});
    std::thread sort_thread(selection_sort, std::ref(drawable_array));
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (const auto* key_pressed =
                           event->getIf<sf::Event::KeyPressed>()) {
                if (key_pressed->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
            }
        }
        window.clear();
        window.draw(drawable_array);
        window.display();
    }

    exit(0);
}
