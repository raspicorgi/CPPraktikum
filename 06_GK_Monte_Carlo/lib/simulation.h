#pragma once
#include <iostream>
#include "grid.h"
#include <vector>

extern std::vector<Rod> rods;

void initializeSimulation();
void performGCMCStep();
int getTotalRods();
void saveConfiguration(const std::string& filename);