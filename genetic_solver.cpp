#include <array>
#include <vector>
#include "genetic_solver.h"
#include <stdlib.h>
#include <exception>

// Check if class T has mutate method
template <typename T>
class has_mutate{
    typedef char mutate_one;
    struct mutate_two { char x2[2]; };

    template <typename C> static mutate_one test( decltype(&C::mutate) ) ;
    template <typename C> static mutate_two test(...);
public:
    static const bool value = sizeof(test<T>(0)) == sizeof(mutate_one);
};

// Check if class T has crossover method
template <typename T>
class has_crossover{
    typedef char crossover_one;
    struct crossover_two { char x3[2]; };

    template <typename C> static crossover_one test( decltype(&C::crossover) ) ;
    template <typename C> static crossover_two test(...);
public:
    static const bool value = sizeof(test<T>(0)) == sizeof(crossover_one);
};

// Check if class T has fitness method
template <typename T>
class has_fitness{
    typedef char fitness_one;
    struct fitness_two { char x4[2]; };

    template <typename C> static fitness_one test( decltype(&C::fitness) ) ;
    template <typename C> static fitness_two test(...);
public:
    static const bool value = sizeof(test<T>(0)) == sizeof(fitness_one);
};

// Check if class T has getBestFit method
template <typename T>
class has_getBestFit
{
    typedef char getBestFit_one;
    struct getBestFit_two { char x1[2]; };

    template <typename C> static getBestFit_one test( decltype(&C::getBestFit) ) ;
    template <typename C> static getBestFit_two test(...);
public:
    static const bool value = sizeof(test<T>(0)) == sizeof(getBestFit_one);
};

// Method to check if class Individual has all methods needed
template<class Individual>
bool GeneticSolver<Individual>::checkConditions(){
    if(!has_getBestFit<Individual>::value){
        std::cout<<"This class has no getBestFit method for Genetic algorithm"<<std::endl;
    } else if(!has_mutate<Individual>::value) {
        std::cout<<"This class has no mutate method for Genetic algorithm"<<std::endl;
    } else if(!has_crossover<Individual>::value) {
        std::cout<<"This class has no crossover method for Genetic algorithm"<<std::endl;
    } else if(!has_fitness<Individual>::value) {
        std::cout<<"This class has no fitness method for Genetic algorithm"<<std::endl;
    } else{
        return true;
    }
    return false;
}

// Defining Genetic solver constructor
template<class Individual>
GeneticSolver<Individual>::GeneticSolver(Individual i) {
    if(checkConditions()){
        this->individual = i;
        this->mutation_count = 10000;
        this->population_size = 10;
    }
}

// solve method
template<class Individual> template<typename T> requires Comparable<T>
Individual GeneticSolver<Individual>::solve(){
    // If no conditions violated
    if(!checkConditions()){
        return this->individual;
    }


    int pop_size = this->population_size;
    int mutations = this->mutation_count;


    T best_fit_1;
    T best_fit_2;


    Individual best = this->individual;
    T best_fit = this->individual.fitness();

    Individual best_individual_1;
    Individual best_individual_2;

    Individual mutated;
    T fit;

    // Genetic algorithm loop
    for(int i1 = 0; i1 < mutations; i1++){
        // Declaring best fitnesses as infinity
        // Finding minimal fitness
        best_fit_1 = std::numeric_limits<T>::infinity();
        best_fit_2 = std::numeric_limits<T>::infinity();

        // Mutate best Individual and check fitness
        for(int i2 = 0; i2 < pop_size; i2++){
            mutated = best.mutate(); // Mutate
            fit = mutated.fitness(); // Find fitness
            if(fit < best_fit_1){ // If fitness less that best
                best_fit_2 = best_fit_1;
                best_individual_2 = best_individual_1;
                best_fit_1 = fit;
                best_individual_1 = mutated;
            } else if(fit < best_fit_2){ // If fitness more than best, but less that second best
                best_fit_2 = fit;
                best_individual_2 = mutated;
            }
        }

        // Do a crossover
        std::vector<Individual> cross = best_individual_1.crossover(best_individual_2);

        // If fitness of one of crossovers better than the best Individual, set best individual to a new one
        if(cross[0].fitness() < best_fit){
            best = cross[0];
            best_fit = cross[0].fitness();
        }
        if(cross[1].fitness() < best_fit){
            best = cross[1];
            best_fit = cross[1].fitness();
        }

        // If
        if(best_fit <= best.getBestFit()){
            break;
        }
    }
    // Return best Individual
    return best;
}


// Set Genetic Algorithm parameters
template <class Individual>
void GeneticSolver<Individual>::setPopulationSize(int p) {
    this->population_size = p;
}

template <class Individual>
void GeneticSolver<Individual>::setMutationCount(int m) {
    this->mutation_count = m;
}