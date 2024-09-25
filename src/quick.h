#pragma once

void QuickSort(std::vector<float> &v, int left, int right) {
    if (left > right) {
        return;
    }

    float pivot = v[(left + right) / 2];

    int i = left;
    int j = right;

    while (i <= j) {
        while (v[i] < pivot) {
            i++;
        }
        while (v[j] > pivot) {
            j--;
        }

        if (i <= j) {
            std::swap(v[i], v[j]);
            i++;
            j--;
        }
    }

    QuickSort(v, left, j);
    QuickSort(v, i, right);
}
