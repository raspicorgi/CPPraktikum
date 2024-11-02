#include "Velocity_Verlet.hpp"

        std::vector<Body> Velocity_Verlet::integrate(const std::vector<Body>& bodies, const double maxTimeStep){
            std::vector<Body> new_bodies;
            for(Body current_body : bodies){
                Body new_current_body = current_body;
                Vector3d acceleration = Tools::calc_acceleration(bodies,current_body);
                new_current_body.setPosition(current_body.getPosition() + current_body.getVelocity() * maxTimeStep + acceleration * 0.5 * pow(maxTimeStep,2));
                Vector3d new_acceleration = Tools::calc_acceleration(bodies,new_current_body);
                new_current_body.setVelocity(current_body.getVelocity() + (acceleration + new_acceleration) * 0.5 * maxTimeStep);
                new_bodies.push_back(new_current_body);
            } 
            return new_bodies;
        }