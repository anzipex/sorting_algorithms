#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <thread>
#include <mutex>

namespace{
std::mutex outputMutex; // synchronizing output
std::map<std::string, clock_t> stats;
}

int RandInt();
float RandFloat();

void Print(const std::vector<float> &v);
void FillVectorManualFloat(std::vector<float> &v, const int &n, char **argv);
void FillVectorRandFloat(std::vector<float> &v, const size_t &n);
void PerformSort(const std::string &sortName, const std::vector<float> &v,
        void (*sortFunc)(std::vector<float> &));

void InsertionSort(std::vector<float> &v);
void SelectionSort(std::vector<float> &v);
void BubbleSort(std::vector<float> &v);
void ShellSort(std::vector<float> &v);
void MergeSort(std::vector<float> &v, int left, int right);
void Merge(std::vector<float> &v, int left, int mid, int right);
void HeapSort(std::vector<float> &v);
void Sink(std::vector<float> &v, size_t i, size_t n);
void QuickSort(std::vector<float> &v, int left, int right);
void QuickSort3Way(std::vector<float> &v, int left, int right);

int RandInt() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 1);
    return dist(gen);
}

float RandFloat() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0F, 1.0F);
    return dist(gen);
}

void Print(const std::vector<float> &v) {
    for (auto el : v) {
        std::cout << el << " ";
    }
    std::cout << '\n';
}

void FillVectorManualFloat(std::vector<float> &v, const int &n, char **argv) {
    for (int i = 1; i <= n; i++) {
        v.push_back(std::stof(argv[i]));
    }
}

void FillVectorRandFloat(std::vector<float> &v, const size_t &n) {
    for (size_t i = 0; i < n; i++) {
        v.push_back(RandFloat());
    }
}

void PerformSort(const std::string &sortName, const std::vector<float> &v,
        void (*sortFunc)(std::vector<float> &)) {
    std::vector<float> tmpV = v;

    const clock_t t1 = clock();
    sortFunc(tmpV);
    const clock_t t2 = clock();
    const clock_t cpuTime = t2 - t1;

    const bool sorted = std::is_sorted(tmpV.begin(), tmpV.end());

    std::lock_guard<std::mutex> lock(outputMutex);
    stats[sortName] = cpuTime;
    std::cout << sortName << ": cpu_time = " << cpuTime << '\n';

    if (!sorted) {
        std::cout << "Error! " << sortName << " is unsorted!" << "\n";
    }
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
    for (size_t i = 0; i < v.size() - 1; i++) {
        bool swapped = false;
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

void MergeSort(std::vector<float> &v, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        MergeSort(v, left, mid);
        MergeSort(v, mid + 1, right);

        Merge(v, left, mid, right);
    }
}

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

int main(int argc, char **argv) {
    const int minArgs = 2;
    if (argc < minArgs) {
        std::cerr << "Error: Not enough arguments. Expected at least " << minArgs - 1
                  << " argument(s).\n";
        return 1;
    }
    if (std::stof(argv[1]) < 0) {
        std::cerr << "Error: The first argument must be a non-negative number.\n";
        return 1;
    }


    std::vector<float> v;
    if (argc == minArgs) {
        FillVectorRandFloat(v, std::stoi(argv[1]));
    } else {
        FillVectorManualFloat(v, argc - 1, argv);
    }

    if (v.empty()) {
        std::cerr << "Error: Array cannot be empty.\n";
        return 1;
    }

    Print(v);

    std::thread insertionThread(PerformSort, "InsertionSort", v, InsertionSort);
    std::thread selectionThread(PerformSort, "SelectionSort", v, SelectionSort);
    std::thread bubbleThread(PerformSort, "BubbleSort", v, BubbleSort);
    std::thread shellThread(PerformSort, "ShellSort", v, ShellSort);
    std::thread mergeThread(PerformSort, "MergeSort", v,
            [](std::vector<float> &v) { MergeSort(v, 0, static_cast<int>(v.size() - 1)); });
    std::thread heapThread(PerformSort, "HeapSort", v, HeapSort);
    std::thread quickThread(PerformSort, "QuickSort", v,
            [](std::vector<float> &v) { QuickSort(v, 0, static_cast<int>(v.size() - 1)); });
    std::thread quick3WayThread(PerformSort, "QuickSort3Way", v,
            [](std::vector<float> &v) { QuickSort3Way(v, 0, static_cast<int>(v.size() - 1)); });

    insertionThread.join();
    selectionThread.join();
    bubbleThread.join();
    shellThread.join();
    mergeThread.join();
    heapThread.join();
    quickThread.join();
    quick3WayThread.join();

    auto minElement = std::min_element(stats.begin(), stats.end(),
            [](const std::pair<std::string, clock_t> &a, const std::pair<std::string, clock_t> &b) {
                return a.second < b.second;
            });

    if (minElement != stats.end()) {
        std::cout << "\nThe fastest sort for now is:\n" << minElement->first
                  << ": cpu_time = " << minElement->second << '\n';
    }

    return 0;
}