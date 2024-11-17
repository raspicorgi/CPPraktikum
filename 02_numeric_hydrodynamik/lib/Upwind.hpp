#ifndef UPWIND_HPP
#define UPWIND_HPP
#include "Density.hpp"
class Upwind {
    public:
        Upwind();
       Density  solve(Density rho(), double sigma);
};

 #endif // UPWIND_HPP