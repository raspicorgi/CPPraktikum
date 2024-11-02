#include "Iterierter_Hermite.hpp"

std::vector<Body> Iterierter_Hermite::integrate(const std::vector<Body>& bodies, const long double maxTimeStep){
    std::vector<Body> newBodies;
    for (const Body& current_body : bodies) {
       Body predicted_body = current_body;
                Body corrected_body = current_body;
                Vector3d initial_acceleration = Tools::calc_acceleration(bodies,current_body);
                Vector3d initial_jerk = Tools::calc_jerk(bodies,current_body);
                predicted_body.setVelocity(current_body.getVelocity() + initial_acceleration * maxTimeStep + initial_jerk * 0.5 * pow(maxTimeStep,2));
                predicted_body.setPosition(current_body.getPosition() + current_body.getVelocity() * maxTimeStep + initial_acceleration * 0.5 * pow(maxTimeStep,2) + initial_jerk *(1/6)* pow(maxTimeStep,3));
                Vector3d predicted_acceleration = Tools::calc_acceleration(bodies,predicted_body);
                Vector3d predicted_jerk = Tools::calc_jerk(bodies,predicted_body);
                corrected_body.setVelocity(current_body.getVelocity() + (predicted_acceleration + initial_acceleration)*0.5*maxTimeStep + (predicted_jerk - initial_jerk)*(1/12)*pow(maxTimeStep,2));
                corrected_body.setPosition(current_body.getPosition() + (corrected_body.getVelocity() + current_body.getVelocity())*0.5*maxTimeStep +(predicted_acceleration - initial_acceleration)*(1/12)*pow(maxTimeStep,2));
                newBodies.push_back(corrected_body);
    }
    return newBodies;
};