#pragma once

#include <vector>
#include <string>

void openOutputFile(const std::string& filename);
void closeOutputFile();
void writeHeader(const unsigned long &steps, const unsigned long &save_freq, const double &activity);
void writeHeaderAllObservables(const unsigned long &steps, const unsigned long &save_freq, const double &activity);
void appendRodCounts(const unsigned long &step);
void appendAllObservables(const unsigned long &step);