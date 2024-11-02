#ifndef ITERIERTER_HERMITE_HPP
#define ITERIERTER_HERMITE_HPP
#include "Integrator.hpp"

class Iterierter_Hermite : public Integrator {
    public:
        std::vector<Body> integrate(const std::vector<Body>& bodies, const double maxTimeStep) override;
};

#endif // ITERIERTER_HERMITE_HPP