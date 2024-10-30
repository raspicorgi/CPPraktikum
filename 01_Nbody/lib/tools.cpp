#include <iostream>
#include "tools.hpp"
#include <vector>
#include "Body.cpp"
#include <cmath>

class tools{
public:
    static std::vector<double> calc_accelaration(std::vector<Body> bodies, Body current_body){
        std::vector<double> accelaration;
        double a_x = 0;
        double a_y = 0;
        double a_z = 0;
        for(Body other_body : bodies){
            if(other_body.is_equal(current_body)){
                continue;
            }
            double dx = abs(other_body.getX() - current_body.getX());
            double dy = abs(other_body.getY() - current_body.getY());
            double dz = abs(other_body.getZ() - current_body.getZ());
            a_x = a_x + G * other_body.getMass() * (dx)/(pow(dx,3));
            a_y = a_y + G * other_body.getMass() * (dy)/(pow(dy,3));
            a_z = a_z + G * other_body.getMass() * (dz)/(pow(dz,3));
        }
        accelaration.push_back(a_x);
        accelaration.push_back(a_y);
        accelaration.push_back(a_z);
        return accelaration;
    }
private:
    const static double G = 6.67430e-11;
};