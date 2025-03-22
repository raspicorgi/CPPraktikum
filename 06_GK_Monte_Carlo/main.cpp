#include <iostream>
#include "lib/simulation.h"
#include "lib/config.h"
#include "lib/output.h"
#include <cmath>

// double beta = 1.0;
// double mu = 0.84;

int main(int argc, char* argv[]) {
    unsigned long thermalization_steps = 2 * pow(10, 7); // Anzahl Schritte zur Thermalisierung
    unsigned long num_steps = 4 * pow(10, 9); // Anzahl simulierter Schritte
    initializeSimulation();

    double activity = 1.1; // Gleich zu exp(beta * mu)
    if (argc > 1) {
        try {
            activity = std::stod(argv[1]);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Ungültiges Aktivitätsargument. Bitte geben Sie eine gültige Zahl ein." << std::endl;
            return 1;
        } catch (const std::out_of_range& e) {
            std::cerr << "Aktivitätsargument außerhalb des Bereichs. Bitte geben Sie eine kleinere Zahl ein." << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Kein Aktivitätsargument angegeben. Standardwert wird verwendet: " << activity << std::endl;
    }
    

    openOutputFile("output/observables" + std::to_string(activity));
    writeHeaderAllObservables(num_steps, save_freq, activity);

    // Thermalisieren
    for (unsigned long i = 0; i < thermalization_steps; i++) {
        performGCMCStep(activity);
    }

    // Simulieren und Daten aufzeichnen
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
        std::cerr << "Fehler: " << e.what() << std::endl;
        closeOutputFile();
        throw;
    } catch (...) {
        std::cerr << "Unbekannter Fehler." << std::endl;
        closeOutputFile();
        throw;
    }

    closeOutputFile();

    // Konfiguration nach Simulation speichern
    saveConfiguration(std::to_string(activity));
    return 0;
}