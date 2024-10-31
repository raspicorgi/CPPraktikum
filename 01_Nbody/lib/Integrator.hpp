#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP
#include "Tools.hpp"

class Integrator {

public:
    virtual ~Integrator();
    virtual std::vector<Body> integrate(const std::vector<Body>* bodies, const double maxTimeStep);
};

#endif // INTEGRATOR_HPP