#include "grid.h"
#include "config.h"
#include <vector>

std::vector<Rod> rods; // Beinhaltet die Koordinaten und Orientierung der Stäbchen
std::vector<std::vector<int>> grid(M, std::vector<int>(M, -1)); // Beinhaltet den Index des Stäbchens, das die jeweilige Position belegt

int periodic(int coord) {
    return (coord + M) % M;
}

int totalRods = 0;
int horizontalRods = 0;
int verticalRods = 0;

void initializeGrid() {
    grid.assign(M, std::vector<int>(M, -1));
}

bool canInsertRod(int x, int y, int s) {
    for (int i = 0; i < L; i++) {
        int px = (s == 1) ? periodic(x + i) : periodic(x);
        int py = (s == -1) ? periodic(y + i) : periodic(y);
        if (grid[px][py] != -1) return false;
    }
    return true;
}

void insertRod(int x, int y, int s) {
    Rod rod = {x, y, s};
    rods.push_back(rod);
    int index = rods.size() - 1;
    for (int i = 0; i < L; i++) {
        int px = (s == 1) ? periodic(x + i) : periodic(x);
        int py = (s == -1) ? periodic(y + i) : periodic(y);
        grid[px][py] = index;
    }
    (s == 1) ? horizontalRods++ : verticalRods++; // update rod counts
    totalRods++;
}

void removeRod(int index) {
    Rod r = rods[index];
    for (int i = 0; i < L; i++) {
        int px = (r.s == 1) ? periodic(r.x + i) : periodic(r.x);
        int py = (r.s == -1) ? periodic(r.y + i) : periodic(r.y);
        grid[px][py] = -1;
    }
    rods.erase(rods.begin() + index);
    (rods[index].s == 1) ? horizontalRods-- : verticalRods--;
    totalRods--;
}
