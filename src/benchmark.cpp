#include "benchmark.hpp"
#include <cmath>
#include <numbers> // std::numbers::pi — C++20, nếu dùng C++17 thì dùng M_PI

namespace benchmark {

static constexpr double PI = std::numbers::pi;

double sphere(const Individual& x) {
    double sum = 0.0;
    for (int i = 0; i < x.size(); ++i) sum += x(i) * x(i);
    return sum;
}

double rosenbrock(const Individual& x) {
    double sum = 0.0;
    for (int i = 0; i + 1 < x.size(); ++i) {
        double a = x(i+1) - x(i) * x(i);
        double b = 1.0 - x(i);
        sum += 100.0 * a * a + b * b;
    }
    return sum;
}

double rastrigin(const Individual& x) {
    double sum = 10.0 * static_cast<double>(x.size());
    for (int i = 0; i < x.size(); ++i) {
        double xi = x(i);
        sum += xi * xi - 10.0 * std::cos(2.0 * PI * xi);
    }
    return sum;
}

BenchmarkProblem make_sphere(int dim) {
    return {
        "Sphere",
        sphere,
        dim,
        -100.0, 100.0,
        0.0
    };
}

BenchmarkProblem make_rosenbrock(int dim) {
    return {
        "Rosenbrock",
        rosenbrock,
        dim,
        -5.0, 10.0,
        0.0
    };
}

BenchmarkProblem make_rastrigin(int dim) {
    return {
        "Rastrigin",
        rastrigin,
        dim,
        -5.12, 5.12,
        0.0
    };
}

} // namespace benchmark