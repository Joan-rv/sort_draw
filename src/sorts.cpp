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

void insertion_sort(DrawableArray& draw_arr) {
    for (size_t i = 1; i < draw_arr.len(); i++) {
        for (size_t j = i; j > 0; j--) {
            if (draw_arr.at(j) < draw_arr.at(j - 1)) {
                draw_arr.swap(j, j - 1);
            } else {
                break;
            }
        }
    }
}
