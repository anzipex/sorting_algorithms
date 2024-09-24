#pragma once

void QuickSort3Way(std::vector<float> &v, int left, int right) {
    if (left >= right) {
        return;
    }

    std::swap(v[left], v[static_cast<size_t>(left) + RandInt() % (right - left + 1)]);
    const float pivot = v[left];

    int lt = left;
    int i = left + 1;
    int gt = right;

    while (i <= gt) {
        if (v[i] < pivot) {
            std::swap(v[lt++], v[i++]);
        } else if (v[i] > pivot) {
            std::swap(v[i], v[gt--]);
        } else {
            i++;
        }
    }

    QuickSort3Way(v, left, lt - 1);
    QuickSort3Way(v, gt + 1, right);
}