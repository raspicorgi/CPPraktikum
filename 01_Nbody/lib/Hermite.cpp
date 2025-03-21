#include "Hermite.hpp"

         std::vector<Body> Hermite::integrate(const std::vector<Body>& bodies, const long double maxTimeStep){
            std::vector<Body> newBodies;
            std::vector<Body> predicted_bodies;
            std::vector<Vector3d> accelerations;
            std::vector<Vector3d> jerks;
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
            for(Body& current_pbody : predicted_bodies){
                Body corrected_body = current_pbody;
                Vector3d predicted_acceleration = Tools::calc_acceleration(predicted_bodies,current_pbody);
                Vector3d predicted_jerk = Tools::calc_jerk(predicted_bodies,current_pbody);
                Vector3d second_derivative_acceleration = (((accelerations[current_pbody.getId()] - predicted_acceleration)*(-3.0)/(pow(maxTimeStep,2))) - ((jerks[current_pbody.getId()]*2.0 + predicted_jerk)/(maxTimeStep)))*2.0 ;
                Vector3d third_derivative_acceleration = (((accelerations[current_pbody.getId()] - predicted_acceleration)*(2.0)/(pow(maxTimeStep,3))) + ((jerks[current_pbody.getId()] + predicted_jerk)/(pow(maxTimeStep,2))))*6.0;
                Vector3d corrected_velocity = current_pbody.getVelocity() + second_derivative_acceleration *(1.0/6.0) * pow(maxTimeStep,3) + third_derivative_acceleration * (1.0/24.0) * pow(maxTimeStep,4);
                Vector3d corrected_position = current_pbody.getPosition() + second_derivative_acceleration * (1.0/24.0) * pow(maxTimeStep,4) + third_derivative_acceleration * (1.0/120.0) * pow(maxTimeStep,5);
                corrected_body.setVelocity(corrected_velocity);
                corrected_body.setPosition(corrected_position);
                newBodies.push_back(corrected_body);
            }
            return newBodies;
        }