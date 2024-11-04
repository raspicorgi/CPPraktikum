#include "Heun.hpp"

std::vector<Body> Heun::integrate(const std::vector<Body>& bodies, const long double maxTimeStep){
    std::vector<Body> newBodies;
    std::vector<Body> k1_bodies;
    std::vector<Body> k2_bodies;
    Vector3d k1_velocity;
    Vector3d k1_position;
    Vector3d k2_velocity;
    Vector3d k2_position;
    for(const Body& current_body : bodies){
        Body k1_body = current_body;
        k1_velocity = Tools::calc_acceleration(bodies, current_body) * maxTimeStep;
        k1_position = current_body.getVelocity() * maxTimeStep;
        k1_body.setVelocity(current_body.getVelocity() + k1_velocity);
        k1_bodies.push_back(k1_body);
    }
    
    for(const Body& current_body : bodies){
        Body new_current_body = current_body;
        k2_velocity = Tools::calc_acceleration(k1_bodies, k1_bodies[current_body.getId()]) * maxTimeStep;
        k2_position = (current_body.getVelocity() + k1_velocity) * maxTimeStep;
        new_current_body.setVelocity(current_body.getVelocity() + (k1_velocity + k2_velocity) *maxTimeStep* 0.5);
        new_current_body.setPosition(current_body.getPosition() + (k1_position + k2_position) *maxTimeStep*0.5);
        newBodies.push_back(new_current_body);
    }
    return newBodies;
}