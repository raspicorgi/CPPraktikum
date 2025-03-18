#include <iostream>
#include "lib/simulation.h"
#include "lib/config.h"
#include "lib/output.h"
#include <cmath>

// double beta = 1.0;
// double mu = 0.84;

int main() {
    unsigned long num_steps = 4l * 1000000000l;  // Number of Monte Carlo steps, equals to 4 * 10^9
    initializeSimulation();

    double activity = exp(beta * mu);

    openOutputFile("output/orientations");
    writeHeader(num_steps, save_freq, beta, mu);

    try {
        for (unsigned long i = 0; i < num_steps; i++) {
            performGCMCStep(activity);
            if (i % save_freq == 0) {
                int total_rods = getTotalRods();
                int horizontal_rods = getRodsWithOrientation(1);
                int vertical_rods = getRodsWithOrientation(-1);
                appendRodCounts(i);
                double eta = L * total_rods / (double) (M * M); // Packungsdichte
                double S = (horizontal_rods - vertical_rods) / (double) total_rods; // Ordnungsparameter
                std::cout << "Step " << i << " (" << (i * 100.0 / num_steps) << "%): " << getTotalRods()
                << " rods (" << getRodsWithOrientation(1) << " horizontal, " << getRodsWithOrientation(-1) << " vertical)"
                << "Eta = " << eta << ", S = " << S << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        closeOutputFile();
        throw; // Re-throw the exception after cleanup
    } catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
        closeOutputFile();
        throw; // Re-throw the exception after cleanup
    }

    closeOutputFile();

    saveConfiguration("output/final_config.txt");
    return 0;
}