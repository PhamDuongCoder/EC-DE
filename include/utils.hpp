#pragma once
#include <vector>
#include <random>
#include <string>
#include <functional>

// Type alias dùng xuyên suốt project
using Individual = std::vector<double>;
using Population = std::vector<Individual>;
using ObjFunc    = std::function<double(const Individual&)>;

// Random engine toàn cục — seed một lần, dùng nhiều nơi
inline std::mt19937& rng() {
    static std::mt19937 engine(std::random_device{}());
    return engine;
}