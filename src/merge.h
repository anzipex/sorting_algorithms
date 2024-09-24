#pragma once

void Merge(std::vector<float> &v, int left, int mid, int right) {
    std::vector<float> tmp(v.begin() + left, v.begin() + mid + 1);

    size_t i = 0;
    int j = mid + 1;
    int k = left;

    while (i < tmp.size() && j <= right) {
        if (v[j] < tmp[i]) {
            v[k++] = v[j++];
        } else {
            v[k++] = tmp[i++];
        }
    }

    while (i < tmp.size()) {
        v[k++] = tmp[i++];
    }
}

void MergeSort(std::vector<float> &v, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        MergeSort(v, left, mid);
        MergeSort(v, mid + 1, right);

        Merge(v, left, mid, right);
    }
}