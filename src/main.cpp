#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

void Print(const std::vector<float> &v);
void FillVectorManual(std::vector<float> &v, const int &n, char **argv);
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
void HeapSort(std::vector<float> &v);
void Sink(std::vector<float> &v, int i, int n);
// =============================================================

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
    int n = v.size();

    // Фаза создания кучи (heapify)
    for (int i = n / 2; i >= 1; --i) {
        Sink(v, i, n); // утопить элементы начиная с середины
    }

    // фаза сортировки (sortdown)
    for (int i = 1; i <= n; ++i) {
        std::swap(v[0], v[n - i]); // поменять корневой элемент с последним
        Sink(v, 1, n - i); // утопить корневой элемент, чтобы восстановить структуру кучи
    }
}

void Sink(std::vector<float> &v, int i, int n) {
    int lc = 2 * i; // левый ребенок
    if (lc > n) return; // нет детей
    int rc = lc + 1; // правый ребенок
    int mc = (rc > n) ? lc : (v[lc - 1] > v[rc - 1]) ? lc : rc; // индекс наибольшего ребенка
    if (v[i - 1] >= v[mc - 1]) return; // если элемент больше или равен наибольшему ребенку, завершить
    std::swap(v[i - 1], v[mc - 1]); // поменять местами текущий элемент с наибольшим ребенком
    Sink(v, mc, n); // рекурсивно утопить следующий элемент
}

int main(int argc, char **argv) {
    srand(time(NULL));

    const int minArgs = 2;
    if (argc < 2 || std::stof(argv[1]) < 0) {
        return 1;
    }

    std::vector<float> v;
    if (argc == minArgs) {
        FillVectorRand(v, std::stoi(argv[1]));
    } else {
        FillVectorManual(v, argc - 1, argv);
    }
    Print(v);

#if 0
    InsertionSort(v);
    SelectionSort(v);
    BubbleSort(v);
    ShellSort(v);
    MergeSort(v, 0, v.size() - 1);
#endif
    HeapSort(v);

    Print(v);

    return 0;
}