#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "lib/Body.cpp"
#include "lib/Integrator.cpp"
#include "lib/Euler_Cromer.cpp"


std::vector<Body> loadBodiesFromFile(const std::string& filename) {
    std::vector<Body> bodies;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        double x, y, z, vx, vy, vz, mass;
        if (iss >> x >> y >> z >> vx >> vy >> vz >> mass) {
            bodies.emplace_back(x, y, z, vx, vy, vz, mass);
        }
    }

    return bodies;
}

int main() {
    //Load data
    std::cout << "Loading data..." << std::endl;
    std::vector<Body> bodies = loadBodiesFromFile("data/2body.txt");
    std::cout << "Data loaded." << std::endl;
    for (const Body& body : bodies) {
        body.printState();
    }
    Euler_Cromer euler_cromer;
    std::vector<Body> new_bodies = euler_cromer.integrate(&bodies, 0.01);  
    for (const Body& body : new_bodies) {
        body.printState();
    }  

/*
    // Test to add vectors
    Vector3d v1(1, 2, 3);
    Vector3d v2(4, 5, 6);
    Vector3d v3 = v1 + v2;
    v3 = v3 * 5;

    std::cout << "(" << v3.getX() << ", " << v3.getY() << ", " << v3.getZ() << ")" << std::endl;
    */
}