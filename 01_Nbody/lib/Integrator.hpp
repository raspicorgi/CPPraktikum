#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP

#include <vector>
#include "Body.hpp"
#include <cmath>
#include "Vector3d.cpp"

class Integrator{

public:
    virtual ~Integrator();
    virtual std::vector<Body> integrate(const std::vector<Body>* bodies, const double maxTimeStep);
};

#endif // INTEGRATOR_HPP