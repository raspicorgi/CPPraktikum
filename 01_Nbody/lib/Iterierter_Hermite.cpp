#include "Iterierter_Hermite.hpp"

std::vector<Body> Iterierter_Hermite::integrate(const std::vector<Body>& bodies, const long double maxTimeStep){
    std::vector<Body> newBodies;
    std::vector<Body> predicted_bodies;
    std::vector<Vector3d> accelerations;
    std::vector<Vector3d> jerks;
    int iterations = 20;
    for(const Body& current_body : bodies)
            {
                Body predicted_body = current_body;
                Vector3d initial_acceleration = Tools::calc_acceleration(bodies,current_body);
                Vector3d initial_jerk = Tools::calc_jerk(bodies,current_body);
                accelerations.push_back(initial_acceleration);
                jerks.push_back(initial_jerk);
                Vector3d predicted_velocity = current_body.getVelocity() + initial_acceleration * maxTimeStep + initial_jerk * 0.5 * pow(maxTimeStep,2);
                Vector3d predicted_position = current_body.getPosition() + current_body.getVelocity() * maxTimeStep + initial_acceleration * 0.5 * pow(maxTimeStep,2) + initial_jerk *(1.0/6.0)* pow(maxTimeStep,3);
                predicted_body.setVelocity(predicted_velocity);
                predicted_body.setPosition(predicted_position);
                predicted_bodies.push_back(predicted_body);
            }
    for(int iter = 0; iter < iterations; iter++){
        for(Body& current_pbody : predicted_bodies){
                Body corrected_body = current_pbody;
                Vector3d predicted_acceleration = Tools::calc_acceleration(predicted_bodies,current_pbody);
                Vector3d predicted_jerk = Tools::calc_jerk(predicted_bodies,current_pbody);
                Vector3d corrected_velocity = bodies[current_pbody.getId()].getVelocity() + (predicted_acceleration + accelerations[current_pbody.getId()]) * 0.5 * maxTimeStep + (predicted_jerk - jerks[current_pbody.getId()]) * (1.0/12.0) * pow(maxTimeStep,2);
                Vector3d corrected_position = bodies[current_pbody.getId()].getPosition() + (corrected_velocity + bodies[current_pbody.getId()].getVelocity()) * 0.5 * maxTimeStep + (predicted_acceleration - accelerations[current_pbody.getId()]) * (1.0/12.0) * pow(maxTimeStep,2);
                corrected_body.setVelocity(corrected_velocity); 
                corrected_body.setPosition(corrected_position);
                newBodies.push_back(corrected_body);
            }
            predicted_bodies = newBodies;
            newBodies.clear();
    }
       return predicted_bodies;
};