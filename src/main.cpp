#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

void Print(const std::vector<float> &v);
void FillVectorRand(std::vector<float> &v, const size_t &n);
float Rand();

void InsertionSort(std::vector<float> &v);
void SelectionSort(std::vector<float> &v);
void BubbleSort(std::vector<float> &v);
void ShellSort(std::vector<float> &v);
// =============================================================
void MergeSort(std::vector<float> &v, uint64_t left, uint64_t right);
void Merge(std::vector<float> &v, uint64_t left, uint64_t mid, uint64_t right);
// =============================================================

void Print(const std::vector<float> &v) {
    for (auto x : v) {
        std::cout << x << " ";
    }
    std::cout << '\n';
}

void FillVectorRand(std::vector<float> &v, const size_t &n) {
    for (size_t i = 0; i < n; i++) {
        v.push_back(Rand());
    }
}

float Rand() {
    return static_cast<float>(rand()) / static_cast<float>(rand());
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

int main(int argc, char **argv) {
    srand(time(NULL));

    if (argc != 2) {
        return 1;
    }

    const size_t n = std::stoi(argv[1]);

    std::vector<float> v;
    FillVectorRand(v, n);
    Print(v);

#if 0
    InsertionSort(v);
    SelectionSort(v);
    BubbleSort(v);
    ShellSort(v);
#endif
    MergeSort(v, 0, v.size() - 1);

    Print(v);

    return 0;
}