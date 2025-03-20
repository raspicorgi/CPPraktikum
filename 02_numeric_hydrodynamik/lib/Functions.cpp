#include "Functions.hpp"

vector<double> Functions::advection(vector <double> &psi, int N , double dt, double dx, vector <double> u){
    vector<double> psi_new = psi;
    psi_new[0] = psi_new[N];
    psi_new[1] = psi_new[N+1]; // Periodische Randbedingungen
    psi_new[N+2] = psi_new[2];
    psi_new[N+3] = psi_new[3];
    vector<double> F_m(N+4,0.0); 
    double psi_adv = 0.0;
    for(int j = 2; j < N+2; j++){
        if(u[j] > 0){
            psi_adv = psi[j-1] +1/2 *(1 - u[j]* dt/dx)* Functions::calc_delta_psi(psi, N, j-1); // GLeichung 2.15
        }
        else{
            psi_adv = psi[j] -1/2 *(1 + u[j]* dt/dx)* Functions::calc_delta_psi(psi, N, j); // GLeichung 2.15
        }
        F_m[j] = psi_adv * u[j]; // Gleichung 2.14
    }
    F_m[0] = F_m[N]; // Periodische Randbedingungen
    F_m[1] = F_m[N+1];
    F_m[N+2] = F_m[2];
    F_m[N+3] = F_m[3];

    for(int j = 2; j < N+2; j++){
        psi_new[j] = psi[j] - dt/dx * (F_m[j+1] - F_m[j]); // Gleichung 2.13 
    }
    return psi_new;
}
    

double Functions::calc_delta_psi(vector <double> &psi, int N, int j){
    if(((psi[j+1] - psi[j]) * (psi[j] - psi[j-1])) > 0){
        return 2*((psi[j+1] - psi[j]) * (psi[j] - psi[j-1]))/(psi[j+1] - psi[j]);
    }
    else{
        return 0.0;
    }
}

void Functions::print_vector(vector<double> &vec){
    for(vector<double>::size_type i = 0; i < vec.size(); i++){
        std::cout << vec[i] << std::endl;
    }
}
