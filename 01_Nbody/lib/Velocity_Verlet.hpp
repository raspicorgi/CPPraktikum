#ifndef VELOCITY_VERLET_HPP
#define VELOCITY_VERLET_HPP
#include "Integrator.hpp"
class Velocity_Verlet : public Integrator {
    private:

        /**
         * @brief Finds a body in the given vector of bodies by its ID.
         * 
         * @param bodies A vector of Body objects to search through.
         * @param id The ID of the body to find.
         * @return The Body object with the specified ID.
         */
        Body findBodyById(const std::vector<Body>& bodies, int id);
    public:
        std::vector<Body> integrate(const std::vector<Body>& bodies, const long double maxTimeStep) override;
};
#endif // VELOCITY_VERLET_HPP