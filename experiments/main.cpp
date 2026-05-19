#include <iostream>
#include "benchmark.hpp"
#include "de.hpp"

using namespace std;

int main() {
    BenchmarkProblem sphere = benchmark::make_rosenbrock(30);
    DEConfig config;
    config.NP = 50;
    config.F = 0.5;
    config.CR = 0.9;
    config.max_gen = 1000;

    DEResult result = de_rand_1_bin(sphere, config);
    cout << "best_fitness = " << result.best_fitness << "\n";
    cout << "fes = " << result.fes;
}