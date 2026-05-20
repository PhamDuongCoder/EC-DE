#include <iostream>
#include <fstream>      // ofstream
#include <vector>
#include "benchmark.hpp"
#include "de.hpp"

using namespace std;

int main(){
    // Mở file CSV để ghi — tạo mới nếu chưa có, overwrite nếu đã có
    ofstream csv("results/params_experiment.csv");
    
    // Ghi header row
    csv << "function,F,CR,run,best_fitness\n";

    // Các giá trị F và CR cần test
    vector<double> F_values  = {0.2, 0.4, 0.6, 0.8, 1.0};
    vector<double> CR_values = {0.1, 0.3, 0.5, 0.7, 0.9};

    auto problems = {
        benchmark::make_sphere(30),
        benchmark::make_rosenbrock(30),
        benchmark::make_rastrigin(30)
    };

    DEConfig config;
    config.NP      = 50;
    config.max_gen = 1000;

    for(const auto& prob : problems){
        cout << "Running: " << prob.name << "\n"; // progress indicator
        for(double F : F_values){
            for(double CR : CR_values){
                config.F  = F;
                config.CR = CR;
                for(int run = 1; run <= 10; run++){
                    DEResult result = de_rand_1_bin(prob, config);
                    
                    // Ghi một row vào CSV
                    // csv << value gống cout << value
                    csv << prob.name << ","
                        << F        << ","
                        << CR       << ","
                        << run      << ","
                        << result.best_fitness << "\n";
                }
            }
        }
    }

    csv.close(); // đóng file
    cout << "Done. Results saved to results/params_experiment.csv\n";
    return 0;
}