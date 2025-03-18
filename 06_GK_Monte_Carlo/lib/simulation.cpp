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
        // Attempt insertion
        int x = getRandomInt(0, M - 1);
        int y = getRandomInt(0, M - 1);
        int s = (getRandom() < 0.5) ? 1 : -1;

        if (canInsertRod(x, y, s)) {
            double acceptance = /*exp(beta * mu)*/ activity * (2 * M * M) / (rods.size() + 1);
            if (getRandom() < std::min(1.0, acceptance)) {
                insertRod(x, y, s);
            }
        }
    } else {
        // Attempt deletion
        if (!rods.empty()) {
            int index = getRandomInt(0, rods.size() - 1);
            double acceptance = (rods.size() / (2.0 * M * M * /*exp(beta*mu)*/ activity));
            if (getRandom() < std::min(1.0, acceptance)) {
                removeRod(index);
            }
        }
    }
}

int getTotalRods() {
    return rods.size();
}

int getRodsWithOrientation(int s) {
    int count = 0;
    for (const Rod& rod : rods) {
        if (rod.s == s) count++;
    }
    return count;
}

void saveConfiguration(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& rod : rods) {
        file << rod.x << " " << rod.y << " " << rod.s << "\n";
    }
    file.close();
}
