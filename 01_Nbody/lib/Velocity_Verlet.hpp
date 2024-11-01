#ifndef VELOCITY_VERLET_HPP
#define VELOCITY_VERLET_HPP
#include "Integrator.hpp"
class Velocity_Verlet : public Integrator {
    public:
            std::vector<Body> integrate(const std::vector<Body>& bodies, const double maxTimeStep) override;
};
#endif // VELOCITY_VERLET_HPP