#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

void Print(const std::vector<float> &v);
void PrintClockDiff(clock_t tStart, clock_t tStop);
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
void MergeSort(std::vector<float> &v, int left, int right);
void Merge(std::vector<float> &v, int left, int mid, int right);
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

void PrintClockDiff(const clock_t tStart, const clock_t tStop) {
    std::cout << "clock diff = " << tStop - tStart << '\n';
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

    const clock_t t1 = clock();
    sortFunc(tmpV);
    const clock_t t2 = clock();
    PrintClockDiff(t1, t2);

    const bool sorted = std::is_sorted(tmpV.begin(), tmpV.end());
    if (!sorted) {
        std::cout << "Error! " << sortName << " is unsorted!" << "\n";
    }

    //Print(tmpV);
}

void InsertionSort(std::vector<float> &v) {
    for (size_t i = 1; i < v.size(); i++) {
        for (size_t j = i; j > 0 && v[j] < v[j - 1]; j--) {
            std::swap(v[j], v[j - 1]);
        }
    }
}

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
    size_t h = 1;
    while (h < v.size() / 3) {
        h = 3 * h + 1; // последовательность Кнута
    }

    while (h >= 1) {
        for (size_t i = h; i < v.size(); i++) {
            float temp = v[i];
            float j = i;

            while (j >= h && v[j - h] > temp) {
                v[j] = v[j - h];
                j -= h;
            }
            v[j] = temp;
        }
        h /= 3;
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

void Merge(std::vector<float> &v, int left, int mid, int right) {
    std::vector<float> temp(v.begin() + left, v.begin() + mid + 1);

    size_t i = 0;
    int j = mid + 1;
    int k = left;

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
        while (v[i] < p) {
            i++;
        }
        while (v[j] > p) {
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

void QuickSort3Way(std::vector<float> &v, int left, int right) {
    if (left >= right) {
        return;
    }

    std::swap(v[left], v[left + rand() % (right - left + 1)]);
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

    //Print(v);

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