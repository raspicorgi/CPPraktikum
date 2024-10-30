#include "Integrator.hpp"

class euler_cromer : public Integrator {
    public:
        std::vector<Body> integrate(const std::vector<Body>* bodies, const double maxTimeStep) override {
            std::vector<Body> newBodies;
            for(Body current_body : *bodies)
            {
                Body new_current_body = current_body;

                newBodies.push_back(new_current_body);
            }
            
            return newBodies;
        }


};
