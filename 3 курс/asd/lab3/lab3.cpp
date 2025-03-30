//
// Created by Максим Прохоров on 29.11.2024.
//

#include "lab3.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <cmath>
#include <numeric>

std::mt19937 random_gen(static_cast<unsigned>(std::time(0)));

const int total_shelves = 5;
const int total_parts = 5;
const double mutation_chance = 0.1;

struct Job { std::vector<int> components; int count; };

std::vector<int> createChromosome() {
    std::vector<int> chromosome(total_parts);
    std::iota(chromosome.begin(), chromosome.end(), 0);
    std::shuffle(chromosome.begin(), chromosome.end(), random_gen);
    return chromosome;
}

int evaluateFitness(const std::vector<int>& chromosome, const std::vector<Job>& jobs) {
    int total_cost = 0;
    for (const auto& job : jobs) {
        int cost = 0;
        for (size_t i = 1; i < job.components.size(); ++i) {
            int pos1 = std::find(chromosome.begin(), chromosome.end(), job.components[i - 1]) - chromosome.begin();
            int pos2 = std::find(chromosome.begin(), chromosome.end(), job.components[i]) - chromosome.begin();
            cost += std::abs(pos1 - pos2);
        }
        total_cost += cost * job.count;
    }
    return total_cost;
}

std::vector<int> breedChromosomes(const std::vector<int>& parent1, const std::vector<int>& parent2) {
    std::vector<int> offspring(total_parts, -1);
    int start_pos = random_gen() % total_parts;
    int end_pos = start_pos + random_gen() % (total_parts - start_pos);

    for (int i = start_pos; i <= end_pos; ++i) {
        offspring[i] = parent1[i];
    }

    for (int i = 0; i < total_parts; ++i) {
        if (std::find(offspring.begin(), offspring.end(), parent2[i]) == offspring.end()) {
            for (int j = 0; j < total_parts; ++j) {
                if (offspring[j] == -1) {
                    offspring[j] = parent2[i];
                    break;
                }
            }
        }
    }
    return offspring;
}

void applyMutation(std::vector<int>& chromosome) {
    if (random_gen() % 100 < static_cast<int>(mutation_chance * 100)) {
        int idx1 = random_gen() % total_parts;
        int idx2 = random_gen() % total_parts;
        std::swap(chromosome[idx1], chromosome[idx2]);
    }
}

void lab3() {
    std::vector<Job> jobs = {
            {{0, 1, 2}, 5},
            {{2, 3, 4}, 3},
            {{0, 4},    2}
    };

    std::vector<int> parent1 = createChromosome();
    std::vector<int> parent2 = createChromosome();

    std::cout << "Parent 1: ";
    for (int val : parent1) std::cout << val << " ";
    std::cout << "\nParent 2: ";
    for (int val : parent2) std::cout << val << " ";
    std::cout << "\n";

    int fitness1 = evaluateFitness(parent1, jobs);
    int fitness2 = evaluateFitness(parent2, jobs);
    std::cout << "Fitness of Parent 1: " << fitness1 << "\n";
    std::cout << "Fitness of Parent 2: " << fitness2 << "\n";

    std::vector<int> offspring = breedChromosomes(parent1, parent2);
    std::cout << "Offspring after crossover: ";
    for (int val : offspring) std::cout << val << " ";
    std::cout << "\n";
}