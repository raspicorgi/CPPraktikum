#include "grid.h"
#include "config.h"
#include <vector>

std::vector<Rod> rods; // Beinhaltet die Koordinaten und Orientierung der Stäbchen
int grid[M][M]; // Beinhaltet den Index des Stäbchens, das die jeweilige Position belegt

int periodic(int coord) {
    return (coord + M) % M;
}

int totalRods = 0;
int horizontalRods = 0;
int verticalRods = 0;

void initializeGrid() {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            grid[i][j] = -1; // Leere Gitterplätze sind -1. Besetzte sind der Index in rods.
        }
    }
}

bool canInsertRod(int x, int y, int s) {
    if (s == 1) {
        for (int i = 0; i < L; i++) {
            int px = periodic(x + i);
            int py = periodic(y);
            if (grid[px][py] != -1) return false;
        }
    } else if (s == -1) {
        for (int i = 0; i < L; i++) {
            int px = periodic(x);
            int py = periodic(y + i);
            if (grid[px][py] != -1) return false;
        }
    }
    return true;
}

void insertRod(int x, int y, int s) {
    Rod rod = {x, y, s};
    rods.push_back(rod);
    int index = rods.size() - 1;
    if (s == 1) {
        for (int i = 0; i < L; i++) {
            int px = periodic(x + i);
            int py = periodic(y);
            grid[px][py] = index;
        }
        horizontalRods++;
    } else if (s == -1) {
        for (int i = 0; i < L; i++) {
            int px = periodic(x);
            int py = periodic(y + i);
            grid[px][py] = index;
        }
        verticalRods++;
    }
    totalRods++;
}

void removeRod(int index) {
    Rod r = rods[index];
    if (r.s == 1) {
        for (int i = 0; i < L; i++) {
            int px = periodic(r.x + i);
            int py = periodic(r.y);
            grid[px][py] = -1;
        }
        horizontalRods--;
    } else if (r.s == -1) {
        for (int i = 0; i < L; i++) {
            int px = periodic(r.x);
            int py = periodic(r.y + i);
            grid[px][py] = -1;
        }
        verticalRods--;
    }
    totalRods--;
    rods.erase(rods.begin() + index);
}
