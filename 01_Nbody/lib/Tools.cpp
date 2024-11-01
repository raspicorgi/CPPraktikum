#include "Tools.hpp"


    

    Vector3d Tools::calc_acceleration(const std::vector<Body>& bodies, Body current_body){
        Vector3d acceleration;
        for(const Body other_body : bodies){
            if(other_body.is_equal(current_body)){
                continue;
            }
            Vector3d r = other_body.getPosition() - current_body.getPosition();
            acceleration = acceleration + (r * (G * other_body.getMass()) / (pow(r.magnitude(), 3)));
        }
        
        return acceleration;
    }

    

    Vector3d Tools::calc_jerk(std::vector<Body> bodies, Body current_body){
        Vector3d jerk;
        for(Body other_body : bodies){
            if(other_body.is_equal(current_body)){
                continue;
            }
            Vector3d r = other_body.getPosition() - current_body.getPosition();
            Vector3d v = other_body.getVelocity() - current_body.getVelocity();
            jerk = jerk + (r * (G * other_body.getMass()) / (pow(r.magnitude(), 3))) - (v * (3 * G * other_body.getMass()) * (r.scalar_product(v)) / (pow(r.magnitude(), 5)));
        }
        return jerk;
    }
