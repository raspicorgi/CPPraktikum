#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP
#include "Tools.hpp"

class Integrator {

public:
    virtual ~Integrator() = default;
    virtual std::vector<Body> integrate(const std::vector<Body>* bodies, const double maxTimeStep) = 0;
};

#endif // INTEGRATOR_HPP