#include <iostream>
#include "grid.h"
#include "simulation.h"
#include "config.h"
#include <experimental/filesystem>

extern std::vector<Rod> rods;

#include <fstream>

std::ofstream outputFile;

#include <filesystem>

void openOutputFile(const std::string& filename) {
    std::string newFilename = filename;
    int index = 1;

    while (std::filesystem::exists(newFilename + ".csv")) {
        newFilename = filename + "_" + std::to_string(index);
        index++;
    }

    newFilename = newFilename + ".csv";

    outputFile.open(newFilename, std::ios::app);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open file " << newFilename << std::endl;
        return;
    }
}

void closeOutputFile() {
    if (outputFile.is_open()) {
        outputFile.close();
    }
}

void writeHeader(const unsigned long &steps, const unsigned long &save_freq, const double &beta, const double &mu) { 
    if (!outputFile.is_open()) {
        std::cerr << "Error: Output file is not open." << std::endl;
        return;
    }
    outputFile << "# Steps: " << steps << std::endl;
    outputFile << "# Save frequency: " << save_freq << std::endl;
    outputFile << "# M: " << M << std::endl;
    outputFile << "# L: " << L << std::endl;
    outputFile << "# beta: " << beta << std::endl;
    outputFile << "# mu: " << mu << std::endl << std::endl;
    outputFile << "# Format: step,total_rods,horizontal_rods,vertical_rods" << std::endl;
}

void appendRodCounts(const unsigned long &step) {
    if (!outputFile.is_open()) {
        std::cerr << "Error: Output file is not open." << std::endl;
        return;
    }
    outputFile << step << "," << getTotalRods() << "," << getRodsWithOrientation(1) << "," << getRodsWithOrientation(-1) << std::endl;
}