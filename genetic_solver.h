//
// Created by Dinislam on 06.06.2021.
//

#ifndef INTERNSHIP_GENETIC_SOLVER_H
#define INTERNSHIP_GENETIC_SOLVER_H

#include <vector>
#include <cstddef>
#include <concepts>

// Creating concept Comparable
template <class T>
concept Comparable = requires (T i1, T i2){
    {i1 == i2} -> std::same_as<bool>;
    {i1 > i2} -> std::same_as<bool>;
    {i2 > i1} -> std::same_as<bool>;
};

// Abstract class Genetic solver
template<class Individual>
class GeneticSolver{
private:
    Individual individual;
    int population_size;
    int mutation_count;
public:
    GeneticSolver(Individual i);
    template<typename T> requires Comparable<T> Individual solve();
    bool checkConditions();
    void setPopulationSize(int p);
    void setMutationCount(int m);
};


#endif //INTERNSHIP_GENETIC_SOLVER_H
