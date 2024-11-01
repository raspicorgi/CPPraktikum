#include "Euler.hpp"

    std::vector<Body> Euler::integrate(const std::vector<Body>& bodies, const double maxTimeStep){
        std::cout << "integrate called" << std::endl;
        std::vector<Body> newBodies;
        std::cout << "before loop" << std::endl;
        for (const Body& body : bodies) {
            Body newBody;
            std::cout << "new body created" << std::endl;
            newBody.setPosition(body.getPosition() + body.getVelocity() * maxTimeStep);
            std::cout << "pos set" << std::endl;
            Vector3d acceleration = Tools::calc_acceleration(bodies, body);
            std::cout << "accel calculated" << std::endl;
            newBody.setVelocity(body.getVelocity() + acceleration * maxTimeStep);
            std::cout << "vel set" << std::endl;
            newBodies.push_back(newBody);
        }
        return newBodies;
    }
