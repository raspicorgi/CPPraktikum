#include "simulation.h"
#include "grid.h"
#include "utils.h"
#include "config.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

// double beta = 1.0;
// double mu = 0.84;

void initializeSimulation() {
    rods.clear();
    initializeGrid();
}


void performGCMCStep(const double &activity) {
    double r = getRandom();
    if (r < 0.5) {
        // Einsetzen
        int x = getRandomInt(0, M - 1);
        int y = getRandomInt(0, M - 1);
        int s = (getRandom() < 0.5) ? 1 : -1;

        if (canInsertRod(x, y, s)) {
            double acceptance = activity * (2 * M * M) / (totalRods + 1);
            if (getRandom() < std::min(1.0, acceptance)) {
                insertRod(x, y, s);
            }
        }
    } else {
        // Entfernen
        if (!rods.empty()) {
            int index = getRandomInt(0, totalRods - 1);
            double acceptance = (totalRods / (2.0 * M * M * activity));
            if (getRandom() < std::min(1.0, acceptance)) {
                removeRod(index);
            }
        }
    }
}


// Konfiguration in Format speichern, dass von bereitgestelltem Python-Skript gelesen werden kann
void saveConfiguration(const std::string& filename_stem) {
    std::string horizontal = filename_stem + "Waagerechte.dat";
    std::string vertikal = filename_stem + "Senkrechte.dat";
    std::ofstream fileHorizontal(horizontal);
    std::ofstream fileVertical(vertikal);
    for (const Rod& rod : rods) {
        if(rod.s == 1) {
            fileHorizontal << rod.x << " " << rod.y << "\n";
        } else {
            fileVertical << rod.x << " " << rod.y << "\n";
        }
    }
    fileHorizontal.close();
    fileVertical.close();
}
