#pragma once

void SelectionSort(std::vector<float> &v) {
    for (size_t i = 0; i < v.size() - 1; ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < v.size(); ++j) {
            if (v[j] < v[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            std::swap(v[i], v[minIndex]);
        }
    }
}