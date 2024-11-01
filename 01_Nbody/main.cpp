#include <iostream>
#include <fstream>
#include <sstream>
#include "lib/Euler_Cromer.hpp"
#include "lib/Euler.hpp"


std::vector<Body> loadBodiesFromFile(const std::string& filename) {
    std::vector<Body> bodies;
    std::ifstream file(filename);
    std::string line;

    int count = 0;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        double x, y, z, vx, vy, vz, mass;
        if (iss >> x >> y >> z >> vx >> vy >> vz >> mass) {
            bodies.emplace_back(count, x, y, z, vx, vy, vz, mass);
        }
        count++;
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
    std::cout << "hier" << std::endl;
    std::vector<Body> newBodies;
    std::cout << "hier2" << std::endl;
    newBodies = Euler().integrate(bodies, 0.01);
    for (const Body& body : newBodies) {
        body.printState();
    }
   
 
    
}