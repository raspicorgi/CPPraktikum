#ifndef TOOLS_HPP
#define TOOLS_HPP
#include <vector>
#include "Body.hpp"
#include "Vector3d.hpp"
#include <cmath>

class Tools{
public:
      static std::vector<double> calc_acceleration(std::vector<Body> bodies, Body current_body);
      static std::vector<double> calc_jerk(std::vector<Body> bodies, Body current_body);
      static Vector3d calc_acceleration_3dvec(std::vector<Body> bodies, Body current_body);
      static Vector3d calc_jerk_3dvec(std::vector<Body> bodies, Body current_body);
private:
    const static double G = 1;
};

#endif // TOOLS_HPP