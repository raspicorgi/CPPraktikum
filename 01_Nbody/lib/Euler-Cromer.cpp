#include "Integrator.hpp"

class euler_cromer : public Integrator {
    public:
        std::vector<Body> integrate(const std::vector<Body>* bodies, const double maxTimeStep) override {
            std::vector<Body> newBodies;
            for(Body current_body : *bodies)
            {
                Body new_current_body = current_body;
                new_current_body.setVx(current_body.getVx() + tools.get_accelaration(current_body.getX()) * maxTimeStep);
                new_current_body.setVy(current_body.getVy() + tools.get_accelaration(current_body.getY()) * maxTimeStep);
                new_current_body.setVz(current_body.getVz() + tools.get_accelaration(current_body.getZ()) * maxTimeStep);
                new_current_body.setX(current_body.getX() + new_current_body.getVx() * maxTimeStep);
                new_current_body.setY(current_body.getY() + new_current_body.getVy() * maxTimeStep);
                new_current_body.setZ(current_body.getY() + new_current_body.getVz() * maxTimeStep);
                newBodies.push_back(new_current_body);
            }
            
            return newBodies;
        }


};
