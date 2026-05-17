#include <iostream>
#include "benchmark.hpp"

int main() {
    // Test tại global optimum — tất cả phải ra 0
    Individual zeros(30, 0.0);
    Individual ones(30, 1.0);

    std::cout << "Sphere   at 0: " << benchmark::sphere(zeros)     << "\n"; // 0
    std::cout << "Rastrigin at 0: " << benchmark::rastrigin(zeros)  << "\n"; // 0
    std::cout << "Rosenbrock at 1: " << benchmark::rosenbrock(ones) << "\n"; // 0

    // Test Rosenbrock tại origin — phải ra 30 (với D=30, mỗi term = 1)
    std::cout << "Rosenbrock at 0: " << benchmark::rosenbrock(zeros) << "\n"; // 30
    return 0;
}