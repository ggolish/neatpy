#include <cmath>
#include <iostream>
#include <vector>

#include "NEAT.h"
#include "utilities.h"

#define POPULATION_SIZE 150
#define NINPUTS 2
#define NOUTPUTS 1
#define THRESHOLD 0.98

std::vector<std::vector<double>> inputs_list {
  {0.0, 0.0},
  {0.0, 1.0},
  {1.0, 0.0},
  {1.0, 1.0}
};

std::vector<double> outputs_list {0.0, 0.0, 0.0, 1.0};

int main()
{
  NEAT neat(POPULATION_SIZE, NINPUTS, NOUTPUTS);
  double best_fitness;
  int best_index;
  for(;;) {
    std::vector<double> fitnesses;
    best_fitness = 0.0;
    best_index = -1;
    for(int i = 0; i < POPULATION_SIZE; ++i) {
      double fitness = 0.0;
      int j = 0;
      for(auto inputs = inputs_list.begin(); inputs != inputs_list.end(); ++inputs) {
        auto outputs = neat.feed_forward(i, (*inputs));
        fitness += fabs(outputs_list[j++] - outputs[0]);
      }
      fitness = 4.0 - fitness;
      fitness *= fitness;
      if(fitness > best_fitness) {
        best_fitness = fitness;
        best_index = i;
      }
      fitnesses.push_back(fitness);
    }
    std::cout << best_fitness << " ";
    for(auto inputs = inputs_list.begin(); inputs != inputs_list.end(); ++inputs) {
      auto outputs = neat.feed_forward(best_index, (*inputs));
      std::cout << outputs[0] << " ";
    }
    std::cout << std::endl;
    if(best_fitness > (16.0 * THRESHOLD)) break;
    neat.repopulate(fitnesses);
  }

  std::cout << *neat.population[best_index] << std::endl;
}
