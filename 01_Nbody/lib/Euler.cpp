#include "Euler.hpp"

    std::vector<Body> Euler::integrate(const std::vector<Body>& bodies, const long double maxTimeStep){
        std::vector<Body> newBodies;
        for (const Body& body : bodies) {
            Body newBody(body.getId());
            newBody.setMass(body.getMass());
            newBody.setPosition(body.getPosition() + body.getVelocity() * maxTimeStep);
            Vector3d acceleration = Tools::calc_acceleration(bodies, body);
            newBody.setVelocity(body.getVelocity() + acceleration * maxTimeStep);
            newBodies.push_back(newBody);
        }
        return newBodies;
    }
