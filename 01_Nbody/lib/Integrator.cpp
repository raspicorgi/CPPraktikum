#include "Integrator.hpp"

Integrator::~Integrator() = default;

std::vector<Body> Integrator::integrate(const std::vector<Body>& bodies, const long double maxTimeStep) {
    // Default implementation, meant to be overwritten
    return std::vector<Body>();
}