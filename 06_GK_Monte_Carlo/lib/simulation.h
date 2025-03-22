#pragma once
#include <iostream>
#include "grid.h"
#include <vector>

extern std::vector<Rod> rods;
extern int totalRods;
extern int horizontalRods;
extern int verticalRods;



void initializeSimulation();
void performGCMCStep(const double &activity);
void saveConfiguration(const std::string& filename);