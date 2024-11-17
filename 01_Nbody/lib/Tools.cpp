#include "Tools.hpp"


    

    Vector3d Tools::calc_acceleration(const std::vector<Body>& bodies, Body current_body){
        Vector3d acceleration;
        for(const Body& other_body : bodies){
            if(other_body.getId() == current_body.getId()){
                continue;
            }
            Vector3d r = other_body.getPosition() - current_body.getPosition();
            acceleration += (r * (G * other_body.getMass())) / (pow(r.magnitude(), 3));
        }
        
        return acceleration;
    }

    

    Vector3d Tools::calc_jerk(const std::vector<Body>& bodies, Body current_body){
        Vector3d jerk;
        for(const Body& other_body : bodies){
            if(other_body.getId() == current_body.getId()){
                continue;
            }
            Vector3d r = other_body.getPosition() - current_body.getPosition();
            Vector3d v = other_body.getVelocity() - current_body.getVelocity();
            jerk += ((v/(pow(r.magnitude(),3)) - ((r*3*v.scalar_product(r))/(pow(r.magnitude(),5))))*(G*other_body.getMass()));
        }
        return jerk;
    }

    Vector3d Tools::specificAngularMomentum(const Body& body){
        return body.getPosition().cross_product(body.getVelocity());
    }

    Vector3d Tools::totalSpecificAngularMomentum(const std::vector<Body>& bodies){
        Vector3d angularMomentum;
        for(const Body& body : bodies){
            angularMomentum += Tools::specificAngularMomentum(body) / body.getMass();
        }
        return angularMomentum;
    }


    Vector3d Tools::rungeLenzVector(const Body& body){
        Vector3d angularMomentum = Tools::specificAngularMomentum(body);
        return (body.getVelocity().cross_product(angularMomentum)) - body.getPosition()/body.getPosition().magnitude(); // skipping the division by total mass because it is normalized to 1
    }

    long double Tools::semiMajorAxis(const Body& body){
        long double specAM = Tools::specificAngularMomentum(body).magnitude();
        long double eccentricity = Tools::rungeLenzVector(body).magnitude();
        return specAM*specAM/(Tools::G*(1-eccentricity*eccentricity));

    }
