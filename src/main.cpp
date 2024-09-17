#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

void Print(const std::vector<float> &v);
void FillVectorRand(std::vector<float> &v, const size_t &n);
float Rand();

void InsertionSort(std::vector<float> &v);
void SelectionSort(std::vector<float> &v);

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
#endif
    SelectionSort(v);

    Print(v);

    return 0;
}