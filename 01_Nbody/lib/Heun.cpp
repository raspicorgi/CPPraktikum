#include "Heun.hpp"
#include <unordered_map>

std::vector<Body> Heun::integrate(const std::vector<Body>& bodies, const long double maxTimeStep){
    std::vector<Body> newBodies;
    std::unordered_map<int, Body> k1_map; // I'm just using a Body to store the positions and velocities together
    std::unordered_map<int, Body> k2_map;

    // loop to calculate k1 values
    for (const Body& body : bodies){
        Body k1_body(body.getId(), body.getMass());
        Vector3d k1_velocity = Tools::calc_acceleration(bodies, body) * maxTimeStep;
        Vector3d k1_position = body.getVelocity() * maxTimeStep;
        k1_body.setVelocity(k1_velocity);
        k1_body.setPosition(k1_position);
        k1_map[body.getId()] = k1_body;
    }

    // loop to calculate k2 values 
    
}