#include <iostream>
#include "grid.h"
#include "simulation.h"
#include "config.h"
#include <experimental/filesystem>
#include <fstream>
#include <filesystem>


extern std::vector<Rod> rods;
std::ofstream outputFile;


// Öffnen und Schließen der Ausgabedatei ist ausgelagert, um Performance zu sparen
void openOutputFile(const std::string& filename) {
    std::string newFilename = filename;
    int index = 1;

    // Nicht überschreiben, sondern neuen Dateinamen generieren
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

// Kommentar am Anfang der Datei schreiben (für nur Stäbchenausrichtungen)
void writeHeader(const unsigned long &steps, const unsigned long &save_freq, const double &activity) { 
    if (!outputFile.is_open()) {
        std::cerr << "Error: Output file is not open." << std::endl;
        return;
    }
    outputFile << "# Steps: " << steps << std::endl;
    outputFile << "# Save frequency: " << save_freq << std::endl;
    outputFile << "# M: " << M << std::endl;
    outputFile << "# L: " << L << std::endl;
    outputFile << "# activity: " << activity << std::endl;
    outputFile << "step,total_rods,horizontal_rods,vertical_rods" << std::endl;
}

// Kommentar am Anfang der Datei schreiben (für alle Observablen)
void writeHeaderAllObservables(const unsigned long &steps, const unsigned long &save_freq, const double &activity){
    if (!outputFile.is_open()) {
        std::cerr << "Error: Output file is not open." << std::endl;
        return;
    }
    outputFile << "# Steps: " << steps << std::endl;
    outputFile << "# Save frequency: " << save_freq << std::endl;
    outputFile << "# M: " << M << std::endl;
    outputFile << "# L: " << L << std::endl;
    outputFile << "# activity: " << activity << std::endl;
    outputFile << "step,total_rods,horizontal_rods,vertical_rods,eta,S" << std::endl;

}

// Stäbchenzahlen in Datei schreiben
void appendRodCounts(const unsigned long &step) {
    if (!outputFile.is_open()) {
        std::cerr << "Error: Output file is not open." << std::endl;
        return;
    }
    outputFile << step << "," << horizontalRods+verticalRods << "," << horizontalRods << "," << verticalRods << std::endl;
}

// Alle Observablen in Datei schreiben
void appendAllObservables(const unsigned long &step) {
    if (!outputFile.is_open()) {
        std::cerr << "Error: Output file is not open." << std::endl;
        return;
    }
    double eta = L * totalRods / (double) (M * M);
    double S = (horizontalRods - verticalRods) / (double) totalRods;
    outputFile << step << "," << horizontalRods+verticalRods << "," << horizontalRods << "," << verticalRods << "," << eta << "," << S << std::endl;
}