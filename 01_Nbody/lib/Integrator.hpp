#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP

#include <vector>
#include "Body.hpp"
#include <cmath>

class Integrator{

public:
    virtual ~Integrator();
    virtual std::vector<Body> integrate(const std::vector<Body>* bodies, const double maxTimeStep);
};

#endif // INTEGRATOR_HPP