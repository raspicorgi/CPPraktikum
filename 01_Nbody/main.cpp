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
#include <string>
#include <cstring>

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


int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <integrator>" << std::endl;
        return 1;
    }

    std::string argument = argv[1];
    
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

    if (argument == "euler") {
        simulate(bodies, iterations, maxTimeStep, Euler);
    } else if (argument == "euler_cromer") {
        simulate(bodies, iterations, maxTimeStep, Euler_Cromer);
    } else if (argument == "velocity_verlet") {
        simulate(bodies, iterations, maxTimeStep, Velocity_Verlet);
    } else if (argument == "hermite") {
        simulate(bodies, iterations, maxTimeStep, Hermite);
    } else if (argument == "iterierter_hermite") {
        simulate(bodies, iterations, maxTimeStep, Iterierter_Hermite);
    } else if (argument == "heun") {
        simulate(bodies, iterations, maxTimeStep, Heun);
    } else if (argument == "rk4") {
        simulate(bodies, iterations, maxTimeStep, RK4);
    } else {
        std::cerr << "Unknown integrator: " << argument << std::endl;
        return 1;
    }

    return 0;
}