#ifndef DENSITY_HPP
#define DENSITY_HPP
#include <vector>
#include <unordered_map> 
#include <cmath>
#include <utility>

class Density {
    public:
        static double rectangle_start_rho(double x);
        void set_Rho(double x, double t,double rho);
        double get_Rho(double x, double t);
    private:
     double x;
     double t;
     std::unordered_map<std::pair<double,double>, double> rho;
};
#endif // DENSITY_HPP
