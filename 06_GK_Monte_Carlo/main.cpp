#include <iostream>
#include "lib/simulation.h"
#include "lib/config.h"

int main() {
    unsigned long num_steps = 4l * 1000000000l;  // Number of Monte Carlo steps
    initializeSimulation();

    for (unsigned long i = 0; i < num_steps; i++) {
        performGCMCStep();
        if (i % 10000000 == 0) {
            int total_rods = getTotalRods();
            int horizontal_rods = getRodsWithOrientation(1);
            int vertical_rods = getRodsWithOrientation(-1);
            double eta = L * total_rods / (double) (M * M); // Packungsdichte
            double S = (horizontal_rods - vertical_rods) / (double) total_rods; // Ordnungsparameter
            std::cout << "Step " << i << " (" << (i * 100.0 / num_steps) << "%): " << getTotalRods() << " rods (" << getRodsWithOrientation(1) << " horizontal, " << getRodsWithOrientation(-1) << " vertical)" << std::endl;
            std::cout << "Eta = " << eta << ", S = " << S << std::endl;
        }
    }

    saveConfiguration("output/final_config.txt");
    return 0;
}