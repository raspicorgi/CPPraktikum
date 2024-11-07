#include "Heun.hpp"


std::vector<Body> Heun::integrate(const std::vector<Body>& bodies, const long double maxTimeStep){
    std::vector<Body> newBodies;
    std::unordered_map<int, Body> k1_map; // I'm just using a Body to store the positions and velocities together.
    std::unordered_map<int, Body> k2_map; // The body has no physical meaning, I just use it as a data structure.
    std::vector<Body> k1_bodies;

    // loop to calculate k1 values
    for (const Body& body : bodies){
        Body k1_body(body.getId(), body.getMass());
        Body k1_mod = body;
        Vector3d k1_velocity = Tools::calc_acceleration(bodies, body) * maxTimeStep; // k1_v
        Vector3d k1_position = body.getVelocity() * maxTimeStep;                     // k1_r
        k1_body.setVelocity(k1_velocity);
        k1_body.setPosition(k1_position);
        k1_mod.setVelocity(body.getVelocity() + k1_velocity);
        k1_mod.setPosition(body.getPosition() + k1_position);
        k1_bodies.push_back(k1_mod);
        k1_map[body.getId()] = k1_body;
    }

    // loop to calculate k2 values 
    for (const Body& body : bodies){
        Body k2_body(body.getId(), body.getMass());
        Body moved_body = body;
        moved_body.setPosition(body.getPosition() + k1_map[body.getId()].getPosition());
        Vector3d k2_velocity = Tools::calc_acceleration(k1_bodies, moved_body) * maxTimeStep;              // k2_v
        Vector3d k2_position = (body.getVelocity() + k1_map[body.getId()].getVelocity())* maxTimeStep; // k2_r
        k2_body.setVelocity(k2_velocity);
        k2_body.setPosition(k2_position);
        k2_map[body.getId()] = k2_body;
    }

    // loop to calculate new bodies with new positions and velocities
    for (const Body& body : bodies){
        Body newBody(body.getId(), body.getMass());
        Vector3d newVelocity = body.getVelocity() + (k1_map[body.getId()].getVelocity() + k2_map[body.getId()].getVelocity()) / 2;
        Vector3d newPosition = body.getPosition() + (k1_map[body.getId()].getPosition() + k2_map[body.getId()].getPosition()) / 2;
        newBody.setVelocity(newVelocity);
        newBody.setPosition(newPosition);
        newBodies.push_back(newBody);
    }
    return newBodies;
}