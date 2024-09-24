#include <iostream>
#include <ctime>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <cctype>
#include <stdexcept>

#include "random.h"
#include "insertion.h"
#include "selection.h"
#include "bubble.h"
#include "shell.h"
#include "merge.h"
#include "heap.h"
#include "quick.h"
#include "quick_three_way.h"

namespace {
std::mutex outputMutex; // synchronizing output
std::map<std::string, clock_t> stats; // names and cpu times
} // namespace

bool CheckArguments(int argc, char **argv);
bool IsValidNumber(const std::string &str);
void Print(const std::vector<float> &v);
void FillVectorManualFloat(std::vector<float> &v, const int &n, char **argv);
void FillVectorRandFloat(std::vector<float> &v, const size_t &n);
void PerformSort(const std::string &sortName, const std::vector<float> &v,
        void (*sortFunc)(std::vector<float> &));


bool CheckArguments(const int argc, char **argv) {
    const int minArgs = 2;
    if (argc < minArgs) {
        std::cerr << "Error: Not enough arguments. Expected at least " << minArgs - 1 << " argument(s).\n";
        return false;
    }

    for (int i = 1; i < argc; ++i) {
        if (!IsValidNumber(argv[i])) {
            std::cerr << "Error: The argument " << i << " must be a valid number.\n";
            return false;
        }
    }

    if (argc == minArgs && std::stof(argv[1]) < 0) {
        std::cerr << "Error: The first argument must be a non-negative number.\n";
        return false;
    }

    return true;
}

bool IsValidNumber(const std::string &str) {
    bool hasDecimalPoint = false;
    uint64_t start = 0;

    if (str[start] == '-' || str[start] == '+') {
        start++;
    }

    for (uint64_t i = start; i < str.size(); ++i) {
        if (str[i] == '.') {
            if (hasDecimalPoint) {
                return false;
            }
            hasDecimalPoint = true;
        } else if (std::isdigit(str[i]) == 0) {
            return false;
        }
    }

    return start < str.size();
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
        std::cout << "Error: " << sortName << " is unsorted!"
                  << "\n";
    }
}

int main(int argc, char **argv) {
    if (!CheckArguments(argc, argv)) {
        return 1;
    }

    std::vector<float> v;
    if (argc == 2) {
        FillVectorRandFloat(v, std::stoi(argv[1]));
    } else {
        FillVectorManualFloat(v, argc - 1, argv);
    }

    if (v.empty()) {
        std::cerr << "Error: Array cannot be empty.\n";
        return 1;
    }

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
        std::cout << "\nThe fastest sort for now is:\n"
                  << minElement->first << ": cpu_time = " << minElement->second << '\n';
    }

    std::sort(v.begin(), v.end());
    std::cout << '\n'; Print(v);

    return 0;
}