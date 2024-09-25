#pragma once

void BubbleSort(std::vector<float> &v) {
    for (size_t i = 0; i < v.size() - 1; i++) {
        bool swapped = false;
        for (size_t j = v.size() - 1; j > i; j--) {
            if (v[j] < v[j - 1]) {
                std::swap(v[j], v[j - 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}
