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

void normalizeMasses(std::vector<Body> bodies) {
    double totalMass = 0;
    for (const Body& body : bodies) {
        totalMass += body.getMass();
    }

    for (Body& body : bodies) {
        body.setMass(body.getMass() / totalMass);
    }
}


int main() {
    //Load data
    
    std::cout << "Loading data...";
    std::vector<Body> bodies = loadBodiesFromFile("data/2body.txt");
    std::cout << " Data loaded." << std::endl;
    std::cout << "Normalizing masses...";
    normalizeMasses(bodies);
    std::cout << " Masses normalized." << std::endl;
    for (const Body& body : bodies) {
        body.printState();
    }
    std::vector<Body> newBodies;
    newBodies = Euler().integrate(bodies, 0.01);
    for (const Body& body : newBodies) {
        body.printState();
    }
   
 
    
}