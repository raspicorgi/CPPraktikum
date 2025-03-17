#include <iostream>
#include "lib/simulation.h"

int main() {
    int num_steps = 1000000;  // Number of Monte Carlo steps
    initializeSimulation();

    for (int i = 0; i < num_steps; i++) {
        performGCMCStep();
        if (i % 10000 == 0) {
            std::cout << "Step " << i << ": " << getTotalRods() << " rods\n";
        }
    }

    saveConfiguration("output/final_config.txt");
    return 0;
}