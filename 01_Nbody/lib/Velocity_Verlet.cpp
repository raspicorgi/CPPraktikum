#include "Velocity_Verlet.hpp"
#include <unordered_map>

Body Velocity_Verlet::findBodyById(const std::vector<Body>& bodies, int id){
    for(const Body& body : bodies){
        if(body.getId() == id){
            return body;
        }
    }
    return Body();
}

std::vector<Body> Velocity_Verlet::integrate(const std::vector<Body>& bodies, const long double maxTimeStep){
    std::vector<Body> new_bodies;
    std::unordered_map<int, Body> body_map;
    for (const Body& body : bodies) {
        body_map[body.getId()] = body;
    }
    // for(const Body& current_body : bodies){
    //     Body new_current_body(current_body.getId(), current_body.getMass());
    //     Vector3d acceleration = Tools::calc_acceleration(bodies, current_body);
    //     new_current_body.setPosition(current_body.getPosition() + current_body.getVelocity() * maxTimeStep + acceleration * 0.5 * pow(maxTimeStep,2));
    //     Vector3d new_acceleration = Tools::calc_acceleration(bodies,new_current_body);
    //     new_current_body.setVelocity(current_body.getVelocity() + (acceleration + new_acceleration) * 0.5 * maxTimeStep);
    //     new_bodies.push_back(new_current_body);
    // } 

    // loop to calculate new positions
    for (const Body& body : bodies){
        Body newBody(body.getId(), body.getMass());
        Vector3d acceleration = Tools::calc_acceleration(bodies, body);
        Vector3d new_position = body.getPosition() + body.getVelocity() * maxTimeStep + acceleration * 0.5 * pow(maxTimeStep, 2);
        newBody.setPosition(new_position);
        newBody.setVelocity(body.getVelocity()); // copy v_n so that we can calculate a_n in the loop below
        new_bodies.push_back(newBody);
    }

    // loop to calculate new velocities
    for (Body& new_body : new_bodies) {
        const Body& original_body = body_map[new_body.getId()];
        Vector3d new_acceleration = Tools::calc_acceleration(new_bodies, new_body);
        Vector3d acceleration = Tools::calc_acceleration(bodies, original_body);
        Vector3d new_velocity = new_body.getVelocity() + (acceleration + new_acceleration) * 0.5 * maxTimeStep;
        new_body.setVelocity(new_velocity);
    }
    return new_bodies;
}