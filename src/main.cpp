#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

void Print(const std::vector<float> &v);
void FillVectorManual(std::vector<float> &v, const int &n, char **argv);
void FillVectorRand(std::vector<float> &v, const size_t &n);
float Rand();

void PerformSort(const std::string &sortName, const std::vector<float> &v,
        void (*sortFunc)(std::vector<float> &));

void InsertionSort(std::vector<float> &v);
void SelectionSort(std::vector<float> &v);
void BubbleSort(std::vector<float> &v);
void ShellSort(std::vector<float> &v);
// =============================================================
void MergeSort(std::vector<float> &v, uint64_t left, uint64_t right);
void Merge(std::vector<float> &v, uint64_t left, uint64_t mid, uint64_t right);
// =============================================================
void HeapSort(std::vector<float> &v);
void Sink(std::vector<float> &v, size_t i, size_t n);
// =============================================================
void QuickSort(std::vector<float> &v, int left, int right);
void QuickSort3Way(std::vector<float> &v, int left, int right);

void Print(const std::vector<float> &v) {
    for (auto x : v) {
        std::cout << x << " ";
    }
    std::cout << '\n';
}

void FillVectorManual(std::vector<float> &v, const int &n, char **argv) {
    for (int i = 1; i <= n; i++) {
        v.push_back(std::stof(argv[i]));
    }
}

void FillVectorRand(std::vector<float> &v, const size_t &n) {
    for (size_t i = 0; i < n; i++) {
        v.push_back(Rand());
    }
}

float Rand() {
    return static_cast<float>(rand()) / static_cast<float>(rand());
}

void PerformSort(const std::string &sortName, const std::vector<float> &v,
        void (*sortFunc)(std::vector<float> &)) {
    std::vector<float> tmpV = v;
    std::cout << sortName << ":\n";
    sortFunc(tmpV);
    Print(tmpV);
}

void InsertionSort(std::vector<float> &v) {
    for (size_t i = 1; i < v.size(); i++) {
        for (size_t j = i; j > 0 && v[j] < v[j - 1]; j--) {
            float temp = v[j];
            v[j] = v[j - 1];
            v[j - 1] = temp;
        }
    }
}

void SelectionSort(std::vector<float> &v) {
    bool swapped = false;
    for (size_t i = 0; i < v.size() - 1; ++i) {
        swapped = false;
        for (size_t j = i + 1; j < v.size(); ++j) {
            if (v[j] < v[i]) {
                std::swap(v[j], v[i]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

void BubbleSort(std::vector<float> &v) {
    bool swapped = false;
    for (size_t i = 0; i < v.size() - 1; i++) {
        swapped = false;
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

void ShellSort(std::vector<float> &v) {
    float h = 1;
    while (h < v.size()) {
        h = 3 * h + 1;
    }

    while (h > 0) {
        h = h / 3;

        for (size_t k = h; k < v.size(); k++) {
            float temp = v[k];
            float j = k;

            while (j >= h && v[j - h] > temp) {
                v[j] = v[j - h];
                j -= h;
            }
            v[j] = temp;
        }
    }
}

void MergeSort(std::vector<float> &v, uint64_t left, uint64_t right) {
    if (left < right) {
        uint64_t mid = left + (right - left) / 2;

        MergeSort(v, left, mid);
        MergeSort(v, mid + 1, right);

        Merge(v, left, mid, right);
    }
}

void Merge(std::vector<float> &v, uint64_t left, uint64_t mid, uint64_t right) {
    using DiffType = std::vector<float>::difference_type;
    std::vector<float> temp(v.begin() + static_cast<DiffType>(left), v.begin() + static_cast<DiffType>(mid + 1));

    size_t i = 0;
    uint64_t j = mid + 1;
    uint64_t k = left;

    while (i < temp.size() && j <= right) {
        if (v[j] < temp[i]) {
            v[k++] = v[j++];
        } else {
            v[k++] = temp[i++];
        }
    }

    while (i < temp.size()) {
        v[k++] = temp[i++];
    }
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

void QuickSort(std::vector<float> &v, int left, int right) {
    if (left > right) {
        return;
    }

    float p = v[(left + right) / 2];

    int i = left;
    int j = right;

    while (i <= j) {
        while (v[i] < p) i++;
        while (v[j] > p) j--;

        if (i <= j) {
            std::swap(v[i], v[j]);
            i++;
            j--;
        }
    }
    QuickSort(v, left, j);
    QuickSort(v, i, right);
}

void QuickSort3Way(std::vector<float> &v, int left, int right) {
    if (left >= right) {
        return;
    }

    std::swap(v[right], v[left + rand() % (right - left + 1)]);

    const float pivot = v[right];
    int i = left;
    int temp = left;
    int j = right;

    while (i < j) {
        if (v[i] < pivot) {
            std::swap(v[i++], v[temp++]);
        } else if (v[i] == pivot) {
            std::swap(v[i], v[--j]);
        } else {
            i++;
        }
    }

    int m = std::min(j - temp, right - j + 1);
    for (int k = 0; k < m; ++k) {
        std::swap(v[j + k], v[right - m + 1 + k]);
    }

    QuickSort3Way(v, left, j - 1);
    QuickSort3Way(v, right - (j - temp), right);
}

int main(int argc, char **argv) {
    srand(time(NULL));

    const int minArgs = 2;
    if (argc < minArgs || std::stof(argv[1]) < 0) {
        return 1;
    }

    std::vector<float> v;
    if (argc == minArgs) {
        FillVectorRand(v, std::stoi(argv[1]));
    } else {
        FillVectorManual(v, argc - 1, argv);
    }

    if (v.empty()) {
        return 1;
    }

    Print(v);

    PerformSort("InsertionSort", v, InsertionSort);
    PerformSort("SelectionSort", v, SelectionSort);
    PerformSort("BubbleSort", v, BubbleSort);
    PerformSort("ShellSort", v, ShellSort);
    PerformSort("MergeSort", v, [](std::vector<float> &v) { MergeSort(v, 0, v.size() - 1); });
    PerformSort("HeapSort", v, HeapSort);
    PerformSort("QuickSort", v, [](std::vector<float> &v) { QuickSort(v, 0, v.size() - 1); });
    PerformSort("QuickSort3Way", v,
            [](std::vector<float> &v) { QuickSort3Way(v, 0, v.size() - 1); });

    return 0;
}