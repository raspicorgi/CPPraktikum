#ifndef TOOLS_HPP
#define TOOLS_HPP
#include "Body.hpp"

class Tools{
public:
      
      static Vector3d calc_acceleration(const std::vector<Body>& bodies, Body current_body);
      static Vector3d calc_jerk(const std::vector<Body>& bodies, Body current_body);
private:
    constexpr static double G = 1;
};

#endif // TOOLS_HPP