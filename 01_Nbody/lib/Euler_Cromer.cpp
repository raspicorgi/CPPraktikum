
#include "Euler_Cromer.hpp"

        std::vector<Body> Euler_Cromer::integrate(const std::vector<Body>& bodies, const double maxTimeStep) {
            std::vector<Body> newBodies;
            for(const Body current_body : bodies)
            {
                Vector3d acceleration = Tools::calc_acceleration(bodies, current_body);
                Body new_current_body = current_body;
                new_current_body.setVx(current_body.getVx() +  acceleration.getX()* maxTimeStep);
                new_current_body.setVy(current_body.getVy() +  acceleration.getY()* maxTimeStep);
                new_current_body.setVz(current_body.getVz() +  acceleration.getZ()* maxTimeStep);
                new_current_body.setX(current_body.getX() + new_current_body.getVx() * maxTimeStep);
                new_current_body.setY(current_body.getY() + new_current_body.getVy() * maxTimeStep);
                new_current_body.setZ(current_body.getY() + new_current_body.getVz() * maxTimeStep);
                newBodies.push_back(new_current_body);
            }
            return newBodies;
        };
        
