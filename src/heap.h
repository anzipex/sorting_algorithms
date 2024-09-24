#pragma once

void Sink(std::vector<float> &v, size_t i, size_t n) {
    const size_t lc = 2 * i;
    if (lc > n) {
        return;
    }
    const size_t rc = lc + 1;
    const size_t mc = (rc > n) ? lc : (v[lc - 1] > v[rc - 1]) ? lc : rc;
    if (v[i - 1] >= v[mc - 1]) {
        return;
    }
    std::swap(v[i - 1], v[mc - 1]);
    Sink(v, mc, n);
}

void HeapSort(std::vector<float> &v) {
    const size_t n = v.size();

    for (size_t i = n / 2; i >= 1; --i) {
        Sink(v, i, n);
    }

    for (size_t i = 1; i <= n; ++i) {
        std::swap(v[0], v[n - i]);
        Sink(v, 1, n - i);
    }
}