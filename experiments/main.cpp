#include <iostream>
#include "benchmark.hpp"
#include "de.hpp"
#include "ga.hpp"

using namespace std;

int main() {
    BenchmarkProblem sphere = benchmark::make_rastrigin(30);
    GAConfig config;

    GAResult result = ga(sphere, config);
    cout << "best_fitness = " << result.best_fitness << "\n";
    cout << "fes = " << result.fes;
}