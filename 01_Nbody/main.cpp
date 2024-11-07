#include <iostream>
#include <fstream>
#include <sstream>
#include "lib/Euler_Cromer.hpp"
#include "lib/Euler.hpp"
#include "lib/Velocity_Verlet.hpp"
#include "lib/Hermite.hpp"
#include "lib/Iterierter_Hermite.hpp"
#include "lib/RK4.hpp"
#include "lib/Heun.hpp"


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

void normalizeMasses(std::vector<Body>& bodies) {
    long double totalMass = 0;
    for (const Body& body : bodies) {
        totalMass += body.getMass();
    }

    for (Body& body : bodies) {
        body.setMass(body.getMass() / totalMass);
    }
}

void simulate(std::vector<Body>& bodies, int iterations, long double maxTimeStep, Integrator& integrator) {
     for (const Body& body : bodies) {
        body.printState();
    }
    // main loop
    std::vector<Body> newBodies;
    for (int i = 1; i <= iterations; i++) {
        newBodies =integrator.integrate(bodies, maxTimeStep);
        std::cout << "Iteration " << i << "/" << iterations << std::endl;
        bodies = newBodies;
    }
    std::cout << "Simulation complete." << std::endl;
    for (const Body& body : newBodies) {
        body.printState();
    }
    
}

void convertToCenterOfMassSystem(std::vector<Body>& bodies) {
    // calculate center of mass
    Vector3d centerOfMass;
    for (const Body& body : bodies) {
        centerOfMass += body.getPosition() * body.getMass();
    }
    

    // offset all bodies
    for (Body& body : bodies) {
        body.setPosition(body.getPosition() - centerOfMass);
    }

    // calculate velocity of COM
    Vector3d centerOfMassVelocity;
    for (const Body& body : bodies) {
        centerOfMassVelocity += body.getVelocity() * body.getMass();
    }

    // offset body velocity
    for (Body& body : bodies) {
        body.setVelocity(body.getVelocity() - centerOfMassVelocity);
    }

}


int main(int argc, char* argv[]) {
    std::cout<<*argv[0]<<std::endl; 
    //prefs
    int iterations = 628;
    long double maxTimeStep = 0.01;

    //Load data
    std::cout << "Loading data... ";
    std::vector<Body> bodies = loadBodiesFromFile("data/2body.txt");
    std::cout << "Data loaded." << std::endl;
    std::cout << "Normalizing masses... ";
    normalizeMasses(bodies);
    std::cout << "Converting to COM system... ";
    convertToCenterOfMassSystem(bodies);
    std::cout << "Preprocessing complete." << std::endl;
    // for (const Body& body : bodies) {
    //     body.printState();
    // }
    Euler Euler;
    Euler_Cromer Euler_Cromer;
    Velocity_Verlet Velocity_Verlet;
    Hermite Hermite;
    Iterierter_Hermite Iterierter_Hermite;
    Heun Heun;
    RK4 RK4;

    switch (*argv[1])
    {
        case 'Euler':
            simulate(bodies, iterations, maxTimeStep, Euler);
            break;
        case 'C':
            simulate(bodies, iterations, maxTimeStep, Euler_Cromer);
            break;
        case 'V':
            simulate(bodies, iterations, maxTimeStep, Velocity_Verlet);
            break;
        case 'H':
            simulate(bodies, iterations, maxTimeStep, Hermite);
            break;
        case 'I':
            simulate(bodies, iterations, maxTimeStep, Iterierter_Hermite);
            break;
        case 'R':
            simulate(bodies, iterations, maxTimeStep, RK4);
            break;
        case 'U':
            simulate(bodies, iterations, maxTimeStep, Heun);
            break;
    }
    return 0;
   
    
    
}