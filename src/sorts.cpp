#include <sorts.hpp>
void bubble_sort(DrawableArray& draw_arr) {
    for (size_t i = 0; i + 1 < draw_arr.len(); i++) {
        for (size_t j = 0; j + i + 1 < draw_arr.len(); j++) {
            if (draw_arr.at(j) > draw_arr.at(j + 1)) {
                draw_arr.swap(j, j + 1);
            }
        }
    }
}
