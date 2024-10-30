#include <vector>
#include "Body.hpp"
#include <cmath>

class Integrator {
public:
    virtual ~Integrator() = default;
    virtual std::vector<Body> integrate(const std::vector<Body>* bodies, const double maxTimeStep) = 0;
};