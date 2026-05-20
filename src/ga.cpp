#include <iostream>
#include <vector>
#include <cfloat>
#include "ga.hpp"
#include "benchmark.hpp"
#include "utils.hpp"

using namespace std;

static Population init_population(const BenchmarkProblem& problem, const GAConfig& config){
    uniform_real_distribution<double> dist(problem.lower, problem.upper);
    Population pop;
    for(int i = 0; i < config.population_size; i++){
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

static Individual tournament_selection(const GAConfig& config, const Population& pop, const vector<double>& fitness){
    vector<bool> chosen = vector<bool>(config.population_size);
    uniform_int_distribution<int> dist(0, config.population_size - 1);

    double best_fitness = DBL_MAX;
    int best_index = -1;

    for(int i = 0; i < config.tournament_size; i++){
        int index = dist(rng());
        while(chosen[index]){
            index = dist(rng());
        }
        chosen[index] = true;
        
        if(best_fitness > fitness[index]){
            best_fitness = fitness[index];
            best_index = index;
        }
    }

    return pop[best_index];
}

static Individual arithmetic_crossover(const Individual& p1, const Individual& p2){
    uniform_real_distribution<double> dist(0, 1);
    double alpha = dist(rng());
    Individual child;

    child = alpha*p1 + (1 - alpha)*p2;

    return child;
}

static Individual gaussian_mutation(const BenchmarkProblem& problem, const GAConfig& config, const Individual& ind){
    double sigma = 0.1*(problem.upper - problem.lower);
    normal_distribution<double> dist_gaussian(0.0, sigma);
    uniform_real_distribution<double> dist_mutation(0, 1);

    Individual mutated_ind = ind;

    for(int i = 0; i < problem.dim; i++){
        if(dist_mutation(rng()) < config.mutation_rate){
            mutated_ind(i) += dist_gaussian(rng());
        }
    }

    clamp_individual(problem, mutated_ind);

    return mutated_ind;
}

GAResult ga(const BenchmarkProblem& problem, const GAConfig& config){
    Population pop = init_population(problem, config);
    vector<double> fitness = evaluate_all(pop, problem.func);

    int best_index = 0; 
    for(int i = 1; i < config.population_size; i++){
        if(fitness[i] < fitness[best_index]) best_index = i; 
    }

    GAResult result;
    result.fes = config.population_size;
    result.convergence.push_back(fitness[best_index]);
    result.best_solution = pop[best_index];
    result.best_fitness = fitness[best_index];

    int gen = 1;
    while(gen < config.iterations){
        Population next_pop;

        next_pop.push_back(pop[best_index]);

        for(int i = 1; i < config.population_size; i++){
            Individual p1 = tournament_selection(config, pop, fitness);
            Individual p2 = tournament_selection(config, pop, fitness);
            
            Individual child;
            uniform_real_distribution<double> dist(0, 1);
            if(dist(rng()) < config.crossover_rate)
                child = arithmetic_crossover(p1, p2);
            else
                child = p1;

            child = gaussian_mutation(problem, config, child);

            next_pop.push_back(child);
        }
        
        pop = next_pop;
        fitness = evaluate_all(pop, problem.func);
        best_index = 0; 
        for(int i = 1; i < config.population_size; i++){
            if(fitness[i] < fitness[best_index]) best_index = i; 
        }

        result.convergence.push_back(fitness[best_index]);
        if(fitness[best_index] < result.best_fitness){
            result.best_fitness = fitness[best_index];
            result.best_solution = pop[best_index];
        }

        result.fes += config.population_size;
        gen++;
    }

    return result;
}