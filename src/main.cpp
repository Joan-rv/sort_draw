#include <SFML/Graphics.hpp>
#include <drawable_array.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "sort_draw");
    DrawableArray<100> drawable_array({800, 400}, 4);
    drawable_array.setPosition({-2, 200});
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

    return 0;
}
