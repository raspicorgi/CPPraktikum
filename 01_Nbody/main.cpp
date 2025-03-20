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
#include <iomanip>
#include <limits>

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

double nearly_zero_to_zero(double value) {
    return (std::abs(value) < std::numeric_limits<double>::epsilon()) ? 0.0 : value;
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

void simulate(std::vector<Body>& bodies, int iterations, long double maxTimeStep, Integrator& integrator, const std::string& filename,const std::string& integratorName) {
    std::ofstream outputFile(filename); // create a new output file or overwrite an existing one
    std::vector<Body> newBodies = bodies;
    std::vector<Body> copy_bodies = bodies;
    outputFile <<   "# column style format: id;time;x;y;z;vx;vy;vz;mass;totalEnergy;totalSpecificAngularMomentum;rungeLenzVector;semiMajorAxis"
                    "\n# this file will be overwritten without any precaution"
                    "\n# used integrator was " + integratorName + "\n";
  if (outputFile.is_open()) {
    // main loop
    for (int i = 0; i <= iterations; i++) {
        newBodies =integrator.integrate(copy_bodies, maxTimeStep);
        copy_bodies = newBodies;
        for(Body current_body : newBodies){
            outputFile <<std::setprecision(17)<< current_body.getId() << ";"
                       << (maxTimeStep * i) << ";"
                       << current_body.getPosition().getX() << ";"
                       << current_body.getPosition().getY() << ";"
                       << current_body.getPosition().getZ() << ";"
                       << current_body.getVelocity().getX() << ";"
                       << current_body.getVelocity().getY() << ";"
                       << current_body.getVelocity().getZ() << ";"
                       << current_body.getMass() << ";"
                       << Tools::totalEnergy(copy_bodies) << ";"
                       << Tools::totalSpecificAngularMomentum(copy_bodies) << ";"
                       << Tools::rungeLenzVector(current_body).magnitude() << ";"
                       << Tools::semiMajorAxis(current_body)
                       << "\n";
        }
        std::cout << "Iteration " << i << "/" << iterations << std::endl;
       
    }
    outputFile.close(); // close the file when done
    std::cout << "Data was written\n";
  }
  else {
    std::cerr << "Error opening file\n";
  }
    std::cout << "Simulation complete." << std::endl;    
}

void convertToCenterOfMassSystem(std::vector<Body>& bodies) {
    // calculate center of mass
    Vector3d centerOfMass;
    long double totalMass = 0;
    for (const Body& body : bodies) {
        centerOfMass += body.getPosition() * body.getMass();
        totalMass += body.getMass();
        
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
    if (argc < 4) {
        std::cerr << "Please enter an integrator and the maximal time step in this order, example: ./name integrator maxTimeStep Nbody" << std::endl;
        return 1;
    }

    
    std::string argument = argv[1];
    std::string nbody = argv[3];
    //prefs
    long double maxTimeStep = std::stold(argv[2]);
    int iterations = 200;

    //Load data
    std::cout << "Loading data... ";
    std::vector<Body> bodies = loadBodiesFromFile("data/" + nbody +".txt");
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
    if (argument == "all"){
        simulate(bodies, iterations, maxTimeStep, Euler,"simulated_data/"+ nbody + "_euler_" + std::to_string(maxTimeStep) +".txt","euler");
        simulate(bodies, iterations, maxTimeStep, Euler_Cromer,"simulated_data/"+ nbody +"_euler_cromer_" + std::to_string(maxTimeStep) +".txt","euler_cromer");
        simulate(bodies, iterations, maxTimeStep, Velocity_Verlet,"simulated_data/"+nbody+"_velocity_verlet_" + std::to_string(maxTimeStep) +".txt","velocity_verlet");
        simulate(bodies, iterations, maxTimeStep, Hermite,"simulated_data/"+nbody+"_hermite_" + std::to_string(maxTimeStep) +".txt","hermite");
        simulate(bodies, iterations, maxTimeStep, Iterierter_Hermite,"simulated_data/"+nbody+"_iterierter_hermite_" + std::to_string(maxTimeStep) +".txt","iterierter_hermite");
        simulate(bodies, iterations, maxTimeStep, Heun,"simulated_data/"+nbody+"_heun_" + std::to_string(maxTimeStep) +".txt","heun");
        simulate(bodies, iterations, maxTimeStep, RK4,"simulated_data/"+nbody+"_rk4_" + std::to_string(maxTimeStep) +".txt","rk4");
    }
    if (argument == "euler") {
        simulate(bodies, iterations, maxTimeStep, Euler,"simulated_data/"+ nbody + "_euler_" + std::to_string(maxTimeStep) +".txt",argument);
    } else if (argument == "euler_cromer") {
        simulate(bodies, iterations, maxTimeStep, Euler_Cromer,"simulated_data/"+ nbody +"_euler_cromer_" + std::to_string(maxTimeStep) +".txt",argument);
    } else if (argument == "velocity_verlet") {
        simulate(bodies, iterations, maxTimeStep, Velocity_Verlet,"simulated_data/"+nbody+"_velocity_verlet_" + std::to_string(maxTimeStep) +".txt",argument);
    } else if (argument == "hermite") {
        simulate(bodies, iterations, maxTimeStep, Hermite,"simulated_data/"+nbody+"_hermite_" + std::to_string(maxTimeStep) +".txt",argument);
    } else if (argument == "iterierter_hermite") {
        simulate(bodies, iterations, maxTimeStep, Iterierter_Hermite,"simulated_data/"+nbody+"_iterierter_hermite_" + std::to_string(maxTimeStep) +".txt",argument);
    } else if (argument == "heun") {
        simulate(bodies, iterations, maxTimeStep, Heun,"simulated_data/"+nbody+"_heun_" + std::to_string(maxTimeStep) +".txt",argument);
    } else if (argument == "rk4") {
        simulate(bodies, iterations, maxTimeStep, RK4,"simulated_data/"+nbody+"_rk4_" + std::to_string(maxTimeStep) +".txt",argument);
    } else {
        std::cerr << "Unknown integrator: " << argument << std::endl;
        return 1;
    }
    std::cout << argv[2]  <<"\n"<<std::endl;
    return 0;
}