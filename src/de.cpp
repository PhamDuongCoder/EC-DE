#include <iostream>
#include <vector>
#include "benchmark.hpp"
#include "de.hpp"
#include "utils.hpp"

using namespace std;

static Population init_population(const BenchmarkProblem& problem, const DEConfig& config){
    uniform_real_distribution<double> dist(problem.lower, problem.upper);
    Population pop;
    for(int i = 0; i < config.NP; i++){
        Individual ind(problem.dim);
        for(int j = 0; j < problem.dim; j++){
            ind(j) = dist(rng());
        }
        pop.push_back(ind);
    }
    return pop;
}

static vector<double> evaluate_all(const Population& pop, const ObjFunc& func){
    vector<double> eval = vector<double>(pop.size());
    for(size_t i = 0; i < pop.size(); i++){
        eval[i] = func(pop[i]);
    }
    return eval;
}

static void clamp_individual(const BenchmarkProblem& problem, Individual& X){
    for(int i = 0; i < X.size(); i++){
        if(X(i) < problem.lower) X(i) = problem.lower;
        else if(X(i) > problem.upper) X(i) = problem.upper;
    }
}

/*
de_rand_1_bin function: receives the population of a generation, returns the population of the next generation and its fitness
3 steps: mutation -> crossover -> selection
1. mutation: create a donor vector: vi
    for each individual i, pick randomly 3 distinct individuals (not including i) indexed r1, r2, r3.
    create donor vector: vi = xr1 + F(xr2 - xr3) with F being the scale factor
2. crossover: create a trial vector: ui
    for each individual i: generate a jrand number from 0 to dim - 1
    for each dimension j: uij = vij if (j = jrand || for a certain possibility CR) else xij
3. selection: greedy selection
    for each individual i:
        xi ascends to the next generation if f(xi) <= f(ui)
        otherwise xi is replaced by ui in the next generation
*/

static pair<Population, vector<double>> de_rand_1_bin(const BenchmarkProblem& problem, const DEConfig& config, const Population& pop, const vector<double>& fitness){
    
    Population next_pop;

    uniform_int_distribution<int> dist_NP(0, config.NP - 1);
    uniform_int_distribution<int> dist_dim(0, problem.dim - 1);
    uniform_real_distribution<double> dist_CR(0, 1);

    //mutation
    Population donors;
    for(int i = 0; i < config.NP; i++){
        int r1, r2, r3;
        bool valid = false;
        while(!valid){
            r1 = dist_NP(rng());
            r2 = dist_NP(rng());
            r3 = dist_NP(rng());
            valid = (i != r1 && i != r2 && i != r3 && r1 != r2 && r2 != r3 && r3 != r1);
        }
        Individual vi = pop[r1] + config.F * (pop[r2] - pop[r3]);
        clamp_individual(problem, vi);
        donors.push_back(vi);
    }
    
    //crossover
    Population trials;
    for(int i = 0; i < config.NP; i++){
        Individual ui = Individual(problem.dim);
        int j_rand = dist_dim(rng());
        for(int j = 0; j < problem.dim; j++){
            if(j == j_rand || dist_CR(rng()) < config.CR){
                ui(j) = donors[i](j);
            }
            else{
                ui(j) = pop[i](j);
            }
        }
        trials.push_back(ui);
    }

    //selection
    vector<double> trial_fitness = evaluate_all(trials, problem.func);
    vector<double> next_fitness;
    for(int i = 0; i < config.NP; i++){
        if(fitness[i] <= trial_fitness[i]){
            next_pop.push_back(pop[i]);
            next_fitness.push_back(fitness[i]);
        }
        else{
            next_pop.push_back(trials[i]);
            next_fitness.push_back(trial_fitness[i]);
        }
    }

    //return next generation and fitness
    return {next_pop, next_fitness};
}

DEResult de_rand_1_bin(const BenchmarkProblem& Problem, const DEConfig& config){
    Population pop = init_population(Problem, config);
    vector<double> fitness = evaluate_all(pop, Problem.func);

    int best_index = 0; 
    for(int i = 1; i < config.NP; i++){
        if(fitness[i] < fitness[best_index]) best_index = i; 
    }

    DEResult result;
    result.fes = config.NP;
    result.convergence.push_back(fitness[best_index]);
    result.best_solution = pop[best_index];
    result.best_fitness = fitness[best_index];

    int gen = 1;

    while(gen < config.max_gen && (config.max_fes == -1 || result.fes + config.NP <= config.max_fes)){
        auto [next_pop, next_fitness] = de_rand_1_bin(Problem, config, pop, fitness);
        
        pop = next_pop;
        fitness = next_fitness;
        for(int i = 0; i < config.NP; i++){
            if(fitness[i] < fitness[best_index]) best_index = i; 
        }

        result.fes += config.NP;
        result.convergence.push_back(fitness[best_index]);
        if(fitness[best_index] < result.best_fitness){
            result.best_solution = pop[best_index];
            result.best_fitness = fitness[best_index];
        }

        gen++;
    }

    return result;
};