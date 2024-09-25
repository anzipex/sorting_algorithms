#pragma once

#include <random>

int RandInt() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 100);
    return dist(gen);
}

float RandFloat() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0F, 100.0F);
    return dist(gen);
}
