#ifndef EULER_CROMER_HPP
#define EULER_CROMER_HPP
#include "Integrator.hpp"


class Euler_Cromer : public Integrator{
    public:
    std::vector<Body> integrate(const std::vector<Body>& bodies, const long double maxTimeStep) override;
};
#endif // EULER_CROMER_HPP