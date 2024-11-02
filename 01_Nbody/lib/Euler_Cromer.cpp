
#include "Euler_Cromer.hpp"

        std::vector<Body> Euler_Cromer::integrate(const std::vector<Body>& bodies, const long double maxTimeStep) {
            std::vector<Body> newBodies;
            for(const Body current_body : bodies)
            {
                Body new_current_body = current_body;
                Vector3d acceleration = Tools::calc_acceleration(bodies, current_body);
                new_current_body.setVelocity(current_body.getVelocity() + acceleration * maxTimeStep);
                new_current_body.setPosition(current_body.getPosition() + new_current_body.getVelocity() * maxTimeStep);
                newBodies.push_back(new_current_body);
            }
            return newBodies;
        };
        
