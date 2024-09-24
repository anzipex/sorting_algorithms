#pragma once

void InsertionSort(std::vector<float> &v) {
    for (size_t i = 1; i < v.size(); i++) {
        for (size_t j = i; j > 0 && v[j] < v[j - 1]; j--) {
            std::swap(v[j], v[j - 1]);
        }
    }
}
