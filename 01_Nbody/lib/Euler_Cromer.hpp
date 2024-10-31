#ifndef EULER_CROMER_HPP
#define EULER_CROMER_HPP
#include "Integrator.hpp"
#include "Tools.hpp"
#include "Body.hpp"

class Euler_Cromer : public Integrator{
    public:
    std::vector<Body> integrate(const std::vector<Body>* bodies, const double maxTimeStep) override;
};
#endif // EULER_CROMER_HPP