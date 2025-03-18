#pragma once
#include <iostream>
#include "grid.h"
#include <vector>

extern std::vector<Rod> rods;

void initializeSimulation();
void performGCMCStep(const double &activity);
int getTotalRods();
int getRodsWithOrientation(int s);
void saveConfiguration(const std::string& filename);