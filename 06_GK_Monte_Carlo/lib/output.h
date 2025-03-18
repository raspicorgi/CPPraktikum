#pragma once

#include <vector>
#include <string>

void openOutputFile(const std::string& filename);
void closeOutputFile();
void writeHeader(const unsigned long &steps, const unsigned long &save_freq, const double &beta, const double &mu);
void appendRodCounts(const unsigned long &step);
