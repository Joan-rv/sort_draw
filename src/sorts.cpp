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

void selection_sort(DrawableArray& draw_arr) {
    for (size_t i = 0; i + 1 < draw_arr.len(); i++) {
        size_t i_min = i, min = draw_arr.at(i);
        for (size_t j = i + 1; j < draw_arr.len(); j++) {
            size_t elem = draw_arr.at(j);
            if (elem < min) {
                min = elem;
                i_min = j;
            }
        }
        draw_arr.swap(i, i_min);
    }
}
