#include <algorithm>
#include <chrono>
#include <drawable_array.hpp>
#include <mutex>
#include <optional>
#include <stdexcept>
#include <thread>
DrawableArray::DrawableArray(size_t n, sf::Vector2u size, unsigned int padding,
                             std::chrono::nanoseconds delay)
    : n(n), size(size), padding(padding), rand_func(std::random_device()()),
      delay(delay),
      sine_sound_buffer("../resources/100Hz_44100Hz_16bit_05sec.wav"),
      sine_sound(sine_sound_buffer), op({None, std::nullopt, std::nullopt}) {
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
    sine_sound.setLooping(true);
    randomise();
}

void DrawableArray::randomise() {
    {
        std::lock_guard<std::mutex> guard(vec_mutex);
        std::shuffle(vec.begin(), vec.end(), rand_func);
    }
}

size_t DrawableArray::len() { return n; }

void DrawableArray::delay_with_sound(size_t val) {
    // sine wave from 100*(0 + 1) to 100*(10 + 1) Hz
    sine_sound.setPitch(static_cast<double>(val) / n * 10.0 + 1.0);
    sine_sound.play();
    std::this_thread::sleep_for(delay);
    sine_sound.pause();
    op = {None, std::nullopt, std::nullopt};
}

size_t DrawableArray::at(size_t i) {
    op = {Read, i, std::nullopt};
    size_t val;
    {
        std::lock_guard<std::mutex> guard(vec_mutex);
        val = vec[i];
    }
    delay_with_sound(val);
    return val;
}

void DrawableArray::write(size_t i, size_t val) {
    op = {Write, i, std::nullopt};
    {
        std::lock_guard<std::mutex> guard(vec_mutex);
        vec[i] = val;
    }
    delay_with_sound(val);
}

void DrawableArray::swap(size_t i, size_t j) {
    op = {Swap, i, j};
    double avg;
    {
        std::lock_guard<std::mutex> guard(vec_mutex);
        std::swap(vec[i], vec[j]);
        avg = static_cast<double>(vec[i] + vec[j]) / 2;
    }
    delay_with_sound(avg);
}

void DrawableArray::draw(sf::RenderTarget& target,
                         sf::RenderStates states) const {
    Operation curr_op = op.load();
    states.transform.combine(getTransform());
    unsigned int rect_width = size.x / n;
    unsigned int rect_height = size.y / n;
    for (size_t i = 0; i < n; i++) {
        sf::Color color = sf::Color::White;
        if (curr_op.param1 == i || curr_op.param2 == i) {
            if (curr_op.type == Read) {
                color = sf::Color::Green;
            } else if (curr_op.type == Swap || curr_op.type == Write) {
                color = sf::Color::Red;
            }
        }
        size_t val;
        {
            std::lock_guard<std::mutex> guard(vec_mutex);
            val = vec[i];
        }
        sf::RectangleShape rect(
            sf::Vector2f(rect_width - padding, rect_height * val));
        rect.setFillColor(color);
        rect.setPosition(
            sf::Vector2f(padding + rect_width * i, rect_height * (n - val)));
        target.draw(rect, states);
    }
}
