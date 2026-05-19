#pragma once
#include "utils.hpp"
#include "benchmark.hpp"
#include <vector>

using namespace std;

struct DEConfig{
    int NP = 50; //population size
    double F = 0.5; //scale factor
    double CR = 0.9; //crossover rate
    int max_gen = 1000; //maximum number of generations
    int max_fes = -1; //max function evaluation, initiated as unlimited
};

struct DEResult{
    int fes; //number of times the objective function is called (or number of generations)
    std::vector<double> convergence; //the best fitness of each generation 
    Individual best_solution; //the fittest individual across all generations
    double best_fitness; //best_solution's fitness
};

//DE/rand/1/bin
DEResult de_rand_1_bin(const BenchmarkProblem& Problem, const DEConfig& config);