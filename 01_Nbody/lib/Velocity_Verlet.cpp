#include "Velocity_Verlet.hpp"

        std::vector<Body> integrate(const std::vector<Body>* bodies, const double maxTimeStep){
            std::vector<Body> new_bodies;
            for(Body current_body : *bodies){
                Body new_current_body = current_body;
                Vector3d acceleration = Tools::calc_acceleration(*bodies,current_body);
                new_current_body.setX(current_body.getX() + current_body.getVx() * maxTimeStep + 0.5 * acceleration.getX()*pow(maxTimeStep,2));
                new_current_body.setY(current_body.getY() + current_body.getVy() * maxTimeStep + 0.5 * acceleration.getY()*pow(maxTimeStep,2));
                new_current_body.setZ(current_body.getZ() + current_body.getVz() * maxTimeStep + 0.5 * acceleration.getZ()*pow(maxTimeStep,2));
                Vector3d new_acceleration = Tools::calc_acceleration(*bodies,new_current_body);
                new_current_body.setVx(current_body.getVx() + 0.5*(acceleration.getX()+new_acceleration.getX())*maxTimeStep);
                new_current_body.setVy(current_body.getVy() + 0.5*(acceleration.getY()+new_acceleration.getY())*maxTimeStep);
                new_current_body.setVz(current_body.getVz() + 0.5*(acceleration.getZ()+new_acceleration.getZ())*maxTimeStep);
                new_bodies.push_back(new_current_body);
            } 
            return new_bodies;
        }