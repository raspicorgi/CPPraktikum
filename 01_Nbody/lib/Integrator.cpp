#include <vector>
#include "Body.hpp"

class Integrator {
public:
    virtual ~Integrator() = default;
    virtual std::vector<Body> integrate(const std::vector<Body>* bodies, const double maxTimeStep) = 0;
};