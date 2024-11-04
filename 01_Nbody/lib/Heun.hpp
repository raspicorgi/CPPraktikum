#ifndef HEUN_HPP
#define HEUN_HPP
#include "Integrator.hpp"

class Heun : public Integrator{
    public:
        std::vector<Body> integrate(const std::vector<Body>& bodies, const long double maxTimeStep) override;
};




#endif // HEUN_HPP