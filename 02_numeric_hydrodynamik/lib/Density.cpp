#include "Density.hpp"

double Density::rectangle_start_rho(double x){
    if(abs(x) >= 1/3){
        return 1.0;
    }
    else{
        return 0;
    }
}
void Density::set_Rho(double x, double t,double rho){
    this->rho[std::make_pair(x,t)] = rho;
}
double Density::get_Rho(double x, double t){
    return this->rho[std::make_pair(x,t)];
}

