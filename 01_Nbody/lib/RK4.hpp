#ifndef RK4_HPP
#define RK4_HPP
#include "Integrator.hpp"
class RK4 : public Integrator {
    public:
        std::vector<Body> integrate(const std::vector<Body>& bodies, const double long maxTimeStep) override;
};
#endif // RK4_HPP