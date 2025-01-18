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

void merge_sort_rec(DrawableArray& draw_arr, size_t l, size_t r) {
    if (r <= l) {
        return;
    }
    size_t m = (l + r) / 2;
    merge_sort_rec(draw_arr, l, m);
    merge_sort_rec(draw_arr, m + 1, r);

    std::vector<size_t> aux(r - l + 1);
    size_t i1 = l, i2 = m + 1, j = 0;
    while (i1 <= m && i2 <= r) {
        size_t elem1 = draw_arr.at(i1), elem2 = draw_arr.at(i2);
        if (elem1 < elem2) {
            aux[j] = elem1;
            i1++;
            j++;
        } else {
            aux[j] = elem2;
            i2++;
            j++;
        }
    }

    while (i1 <= m) {
        aux[j] = draw_arr.at(i1);
        i1++;
        j++;
    }

    while (i2 <= r) {
        aux[j] = draw_arr.at(i2);
        i2++;
        j++;
    }

    for (size_t i = 0; i <= r - l; i++) {
        draw_arr.write(l + i, aux[i]);
    }
}

void merge_sort(DrawableArray& draw_arr) {
    if (draw_arr.len() > 0) {
        merge_sort_rec(draw_arr, 0, draw_arr.len() - 1);
    }
}
