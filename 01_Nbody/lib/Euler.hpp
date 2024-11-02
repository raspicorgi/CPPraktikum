#ifndef EULER_HPP
#define EULER_HPP
#include "Integrator.hpp"


class Euler : public Integrator{
    public:
    std::vector<Body> integrate(const std::vector<Body>& bodies, const long double maxTimeStep) /*override*/;
};
#endif // EULER_HPP