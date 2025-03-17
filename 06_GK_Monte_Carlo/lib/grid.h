#pragma once
#include <vector>

struct Rod{
    int x, y, s; // x- und y-Koordinate des Stäbchens, s = 1 für horizontal, s = -1 für vertikal
};

extern std::vector<Rod> rods;

void initializeGrid();
bool canInsertRod(int x, int y, int s);
void insertRod(int x, int y, int s);
void removeRod(int index);
int periodic(int coord);