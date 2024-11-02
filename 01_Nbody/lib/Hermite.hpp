#ifndef HERMITE_HPP
#define HERMITE_HPP
#include "Integrator.hpp"

class Hermite : public Integrator {
    public:
        std::vector<Body> integrate(const std::vector<Body>& bodies, const double maxTimeStep) override;
};
#endif // HERMITE_HPP