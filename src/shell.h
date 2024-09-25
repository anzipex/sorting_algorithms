#pragma once

void ShellSort(std::vector<float> &v) {
    size_t h = 1;
    while (h < v.size() / 3) {
        h = 3 * h + 1; // Knuth sequence
    }

    while (h >= 1) {
        for (size_t i = h; i < v.size(); i++) {
            float tmp = v[i];
            size_t j = i;

            while (j >= h && v[j - h] > tmp) {
                v[j] = v[j - h];
                j -= h;
            }
            v[j] = tmp;
        }
        h /= 3;
    }
}
