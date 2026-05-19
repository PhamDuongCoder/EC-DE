#pragma once
#include "utils.hpp"
#include <string>
#include <limits>

using namespace std;

// Mô tả đầy đủ một bài toán benchmark
struct BenchmarkProblem {
    std::string  name;
    ObjFunc      func;
    int          dim;
    double       lower;      // bound đồng nhất cho tất cả chiều
    double       upper;
    double       known_optimum; // dùng để tính error
};

namespace benchmark {

// ── Ba hàm core ──────────────────────────────────────────────────────────────

// Sphere: f(x) = sum(x_i^2)
// Đơn giản nhất, dùng để verify algorithm đúng không
double sphere(const Individual& x);

// Rosenbrock: f(x) = sum[ 100*(x_{i+1} - x_i^2)^2 + (1 - x_i)^2 ]
// Valley hẹp, cong — gradient-based dễ bị lừa, test exploitation
double rosenbrock(const Individual& x);

// Rastrigin: f(x) = 10D + sum[ x_i^2 - 10*cos(2*pi*x_i) ]
// Nhiều local optima đều đặn — test khả năng thoát local optima
double rastrigin(const Individual& x);

// ── Factory: trả về BenchmarkProblem ready-to-use ────────────────────────────
BenchmarkProblem make_sphere    (int dim = 30);
BenchmarkProblem make_rosenbrock(int dim = 30);
BenchmarkProblem make_rastrigin (int dim = 30);

} // namespace benchmark