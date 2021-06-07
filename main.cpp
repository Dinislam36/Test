#include <iostream>
#include <vector>
#include "genetic_solver.cpp"



class TestClass{
public:
    int i;

    TestClass(){
        this->i = 0;
    };

    TestClass(int r){
        this->i = r;
    }
    int getBestFit(){
        return 2;
    }
    TestClass mutate(){
        TestClass temp = TestClass(3);
        return temp;
    }
    std::vector<TestClass> crossover(TestClass t){
        std::vector<TestClass> temp;
        temp.push_back(TestClass(4));
        temp.push_back(TestClass(5));
        return temp;
    }
    int fitness(){
        return 5;
    }
};


int main() {
    std::cout << "Hello, World!" << std::endl;
    GeneticSolver g = GeneticSolver(TestClass(2));
    g.setMutationCount(1000);
    g.setPopulationSize(10);
    TestClass best = g.solve<int>();
    std::cout<<best.fitness();
    return 0;
}
//l
