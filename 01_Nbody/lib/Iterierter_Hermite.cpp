#include "Iterierter_Hermite.hpp"

std::vector<Body> Iterierter_Hermite::integrate(const std::vector<Body>& bodies, const long double maxTimeStep){
    std::vector<Body> newBodies;
    std::vector<Body> predicted_bodies;
    for (const Body& current_body : bodies) {
       Body predicted_body = current_body;
                Vector3d initial_acceleration = Tools::calc_acceleration(bodies,current_body);
                Vector3d initial_jerk = Tools::calc_jerk(bodies,current_body);
                predicted_body.setVelocity(current_body.getVelocity() + initial_acceleration * maxTimeStep + initial_jerk * 0.5 * pow(maxTimeStep,2));
                predicted_body.setPosition(current_body.getPosition() + current_body.getVelocity() * maxTimeStep + initial_acceleration * 0.5 * pow(maxTimeStep,2) + initial_jerk *(1.0/6.0)* pow(maxTimeStep,3));
                predicted_bodies.push_back(predicted_body);
    }
    for (Body& current_body : predicted_bodies) {
                Body corrected_body = current_body;
                Vector3d predicted_acceleration = Tools::calc_acceleration(predicted_bodies,current_body);
                Vector3d predicted_jerk = Tools::calc_jerk(predicted_bodies,current_body);
                Vector3d initial_acceleration = Tools::calc_acceleration(bodies,bodies[current_body.getId()]);
                Vector3d initial_jerk = Tools::calc_jerk(bodies,bodies[current_body.getId()]);
                corrected_body.setVelocity(current_body.getVelocity() + (predicted_acceleration + initial_acceleration)*0.5*maxTimeStep + (predicted_jerk - initial_jerk)*(1.0/12.0)*pow(maxTimeStep,2));
                corrected_body.setPosition(current_body.getPosition() + (corrected_body.getVelocity() + current_body.getVelocity())*0.5*maxTimeStep +(predicted_acceleration - initial_acceleration)*(1.0/12.0)*pow(maxTimeStep,2));
                newBodies.push_back(corrected_body);
    }
    return newBodies;
};