#pragma once
#include <vector>
#include <random>
#include <string>
#include <functional>
#include <Eigen/Dense>

using namespace std;

// Type alias dùng xuyên suốt project
using Individual = Eigen::VectorXd;
using Population = std::vector<Eigen::VectorXd>;
using ObjFunc    = std::function<double(const Individual&)>;

// Random engine toàn cục — seed một lần, dùng nhiều nơi
inline std::mt19937& rng() {
    static std::mt19937 engine(std::random_device{}());
    return engine;
}

