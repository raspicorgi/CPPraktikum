#include "grid.h"
#include "config.h"
#include <vector>

std::vector<std::vector<int>> grid(M, std::vector<int>(M, -1));
std::vector<Rod> rods;

int periodic(int coord) {
    return (coord + M) % M;
}

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
}

void removeRod(int index) {
    Rod r = rods[index];
    for (int i = 0; i < L; i++) {
        int px = (r.s == 1) ? periodic(r.x + i) : periodic(r.x);
        int py = (r.s == -1) ? periodic(r.y + i) : periodic(r.y);
        grid[px][py] = -1;
    }
    rods.erase(rods.begin() + index);
}
