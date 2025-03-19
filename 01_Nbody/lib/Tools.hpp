#ifndef TOOLS_HPP
#define TOOLS_HPP
#include "Body.hpp"

class Tools{
public:
      
    static Vector3d calc_acceleration(const std::vector<Body>& bodies, Body current_body);
    static Vector3d calc_jerk(const std::vector<Body>& bodies, Body current_body);
    static Vector3d specificAngularMomentum(const Body& body);
    static long double totalSpecificAngularMomentum(const std::vector<Body>& bodies);
    static Vector3d rungeLenzVector(const Body& body);
    static long double semiMajorAxis(const Body &body);
    static long double totalEnergy(const std::vector<Body>& bodies);

private:
    constexpr static long double G = 1;
};

#endif // TOOLS_HPP