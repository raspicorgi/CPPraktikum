#include "Hermite.hpp"

         std::vector<Body> Hermite::integrate(const std::vector<Body>& bodies, const long double maxTimeStep){
            std::vector<Body> newBodies;
            std::vector<Body> predicted_bodies;
            for(const Body& current_body : bodies)
            {
                Body predicted_body = current_body;
                Vector3d initial_acceleration = Tools::calc_acceleration(bodies,current_body);
                Vector3d initial_jerk = Tools::calc_jerk(bodies,current_body);
                predicted_body.setVelocity(current_body.getVelocity() + initial_acceleration * maxTimeStep + initial_jerk * 0.5 * pow(maxTimeStep,2));
                predicted_body.setPosition(current_body.getPosition() + current_body.getVelocity() * maxTimeStep + initial_acceleration * 0.5 * pow(maxTimeStep,2) + initial_jerk *(1.0/6.0)* pow(maxTimeStep,3));
                predicted_bodies.push_back(predicted_body);
                
            }
            for(Body& current_body : predicted_bodies){
                Body corrected_body = current_body;
                Vector3d predicted_acceleration = Tools::calc_acceleration(predicted_bodies,current_body);
                Vector3d predicted_jerk = Tools::calc_jerk(predicted_bodies,current_body);
                Vector3d initial_acceleration = Tools::calc_acceleration(bodies,bodies[current_body.getId()]);
                Vector3d initial_jerk = Tools::calc_jerk(bodies,bodies[current_body.getId()]);
                Vector3d second_derivative_acceleration = ((initial_acceleration - predicted_acceleration)*(-3.0)/(pow(maxTimeStep,2)) - (((initial_jerk * 2.0)+predicted_jerk)/(maxTimeStep) )) * 2.0;
                Vector3d third_derivative_acceleration = ((initial_acceleration - predicted_acceleration)*(2.0)/(pow(maxTimeStep,3))) + (((initial_jerk + predicted_jerk)/(pow(maxTimeStep,2))))*6.0;
                corrected_body.setVelocity(current_body.getVelocity() + second_derivative_acceleration *(1.0/6.0) * pow(maxTimeStep,3) + third_derivative_acceleration * (1.0/24.0) * pow(maxTimeStep,4));
                corrected_body.setPosition(current_body.getPosition() + second_derivative_acceleration * (1.0/24.0) * pow(maxTimeStep,4) + third_derivative_acceleration * (1.0/120.0) * pow(maxTimeStep,5));
                newBodies.push_back(corrected_body);
            }
            return newBodies;
        }