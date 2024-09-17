#include <iostream>
#include <vector>
#include <ctime>

void Print(std::vector<float> &v);
void FillVectorRand(std::vector<float> &v, const size_t &n);
float RandFloat();

void Print(std::vector<float> &v) {
    for (auto x : v) {
        std::cout << x << " ";
    }
    std::cout << '\n';
}

void FillVectorRand(std::vector<float> &v, const size_t &n) {
    for (size_t i = 0; i < n; i++) {
        v.push_back(RandFloat());
    }
}

float RandFloat() {
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

int main(int argc, char **argv) {
    srand(time(NULL));

    if (argc != 2) {
        return 1;
    }

    const size_t n = std::stoi(argv[1]);

    std::vector<float> v;
    FillVectorRand(v, n);
    Print(v);

    InsertionSort(v);

    Print(v);

    return 0;
}