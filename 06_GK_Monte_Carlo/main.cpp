#include <iostream>
#include "lib/simulation.h"
#include "lib/config.h"
#include "lib/output.h"
#include <cmath>

// double beta = 1.0;
// double mu = 0.84;

int main(int argc, char* argv[]) {
    unsigned long thermalization_steps = 2 * pow(10, 7);
    unsigned long num_steps = 4 * pow(10, 9); // Number of steps in Monte Carlo simulation
    initializeSimulation();

    double activity = 1.1; //exp(beta * mu);
    if (argc > 1) {
        try {
            activity = std::stod(argv[1]);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid activity argument. Please provide a valid number." << std::endl;
            return 1;
        } catch (const std::out_of_range& e) {
            std::cerr << "Activity argument out of range. Please provide a smaller number." << std::endl;
            return 1;
        }
    } else {
        std::cerr << "No activity argument provided. Using default value: " << activity << std::endl;
    }
    openOutputFile("output/observables" + std::to_string(activity));
    writeHeaderAllObservables(num_steps, save_freq, activity);

    // thermalization
    for (unsigned long i = 0; i < thermalization_steps; i++) {
        performGCMCStep(activity);
    }

    // data collection
    try {
        for (unsigned long i = 0; i < num_steps; i++) {
            performGCMCStep(activity);
            if (i % save_freq == 0) {
                appendAllObservables(i);
            }
            if (i % print_freq == 0) {
                std::cout << "Step " << i << " (" << (i * 100.0 / num_steps) << "%): " <<std::endl;
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