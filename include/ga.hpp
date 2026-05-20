#pragma once
#include "utils.hpp"
#include "benchmark.hpp"
#include <vector>

using namespace std;

struct GAConfig{
    int population_size = 50;
    double crossover_rate = 0.5;
    double mutation_rate = 0.05;
    int iterations = 1000;
    int tournament_size = 5;
};

struct GAResult{
    int fes;
    vector<double> convergence;
    double best_fitness;
    Individual best_solution;
};

GAResult ga(const BenchmarkProblem& problem, const GAConfig& config);