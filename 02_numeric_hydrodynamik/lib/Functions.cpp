#include "Functions.hpp"

vector<double> Functions::advection(vector<double> psi, double N , double dt, double dx, vector<double> u, double t_max){
    double t = 0.0;
    vector<double> psi_copy = psi;
    while(t <= t_max){
        vector<double> psi_new = psi_copy;
        psi_new[0] = psi_new[N];
        psi_new[1] = psi_new[N+1]; // Periodische Randbedingungen
        psi_new[N+2] = psi_new[2];
        psi_new[N+3] = psi_new[3];
        vector<double> F_m(N+4,0.0); 
        double psi_adv = 0.0;
        for(double j = 2; j <= N+2; j++){
            if(u[j] > 0.0){
                double delta_psi = Functions::calc_delta_rho(psi_copy, N, j-1);
                psi_adv = psi_copy[j-1] + 0.5 *(1 - u[j]* (dt/dx))* delta_psi; // Gleichung 2.15

            
        }
        else{
            double delta_psi = Functions::calc_delta_rho(psi_copy, N, j);
            psi_adv = psi_copy[j] - 0.5 *(1 + u[j]* (dt/dx))* delta_psi; // Gleichung 2.15
        }
        F_m[j] = psi_adv * u[j]; // Gleichung 2.14
    }
        F_m[0] = F_m[N]; // Periodische Randbedingungen
        F_m[1] = F_m[N+1];
        F_m[N+2] = F_m[2];
        F_m[N+3] = F_m[3];

        for(double j = 2; j <= N+1; j++){
            psi_new[j] = psi_copy[j] - dt/dx * (F_m[j+1] - F_m[j]); // Gleichung 2.13 
        }
        psi_copy = psi_new;
        t += dt;
    }
    return psi_copy;
    
}
    
double Functions::calc_delta_rho(vector<double> rho, double N, int j){
    double num = ((rho[j+1] - rho[j]) * (rho[j] - rho[j-1]));
    if( num > 0.0){
        if (std::abs(rho[j+1] - rho[j-1]) < 1e-10) {
            return 0.0;
        }
        double delta_rho = 2.0*num/(rho[j+1] - rho[j-1]);
        return delta_rho;
        
    }
    else{
        return 0.0;
    }
}

double Functions::calc_delta_u(vector<double> u, double N, int j){
    double num = ((u[j+1] - u[j]) * (u[j] - u[j-1]));
    if(num > 0.0){
        double delta_u = 2.0 * num/(u[j+1] - u[j-1]) + 1e-10;
        return delta_u;
    }
    else{
        return 0.0;
    }
}

double Functions::calc_delta_epsilon(vector<double> epsilon, double N, int j){
    double num = ((epsilon[j+1] - epsilon[j]) * (epsilon[j] - epsilon[j-1]));
    if(num > 0.0){
        double delta_epsilon = 2.0 * num/(epsilon[j+1] - epsilon[j-1]) + 1e-10;
        return delta_epsilon;
    }
    else{
        return 0.0;
    }
}

vector<double> Functions::rho_advection(vector<double> rho, double N , double dt, double dx, vector <double> u){
    vector <double> rho_adv(N+4,0.0);
    for(double j = 2; j <= N+2; j++){
        if(u[j] > 0.0){
            double delta_rho = Functions::calc_delta_rho(rho, N, j-1);
            rho_adv[j] = rho[j-1] + 0.5 *(1 - u[j]* (dt/dx))* delta_rho; // Gleichung 2.15
        }
        else{
            double delta_rho = Functions::calc_delta_rho(rho, N, j);
            rho_adv[j] = rho[j] - 0.5 *(1 + u[j]* (dt/dx))* delta_rho; // Gleichung 2.15
        }
    }
    return rho_adv;
}

vector<double> Functions::u_advection(vector<double> u, double N , double dt, double dx){
    vector <double> u_adv(N+4,0.0);
    for(double j = 2; j <= N+2; j++){
        double u_mittel = 0.5* (u[j] + u[j+1]);
        if(u_mittel > 0.0){
            double delta_u = Functions::calc_delta_u(u, N, j);
            u_adv[j] = u[j] + 0.5 *(1 - u_mittel* (dt/dx))* delta_u; // Gleichung 2.15
        }
        else{
            double delta_u = Functions::calc_delta_u(u, N, j+1);
            u_adv[j] = u[j+1] - 0.5*(1+ u_mittel* (dt/dx))* delta_u; // Gleichung 2.15
        }
    }
    return u_adv;
}

vector<double> Functions::epsilon_advection(vector<double> epsilon, double N , double dt, double dx, vector <double> u){
    vector <double> epsilon_adv(N+4,0.0);
    for(double j = 2; j <= N+2; j++){
        if(u[j] > 0.0){
            double delta_epsilon = Functions::calc_delta_epsilon(epsilon, N, j-1);
            epsilon_adv[j] = epsilon[j-1] + 0.5 *(1 - u[j]* (dt/dx))* delta_epsilon; // Gleichung 2.15
        }
        else{
            double delta_epsilon = Functions::calc_delta_epsilon(epsilon, N, j);
            epsilon_adv[j] = epsilon[j] - 0.5 *(1 + u[j]* (dt/dx))* delta_epsilon; // Gleichung 2.15
        }
    }
    return epsilon_adv;
}

vector<vector<double>> Functions::calc_F(vector<double> rho, vector<double> u, vector<double> epsilon, double N, double dt, double dx){
    vector<double> F_m(N+4,0.0);
    vector<double> F_I(N+4,0.0);
    vector<double> F_e(N+4,0.0);
    vector<vector<double>> F;
    vector<double> rho_adv = Functions::rho_advection(rho, N, dt, dx, u);
    vector<double> u_adv = Functions::u_advection(u, N, dt, dx);
    vector<double> epsilon_adv = Functions::epsilon_advection(epsilon, N, dt, dx, u);
    for(double j = 2; j <= N+2; j++){
       F_m[j] = rho_adv[j] * u[j];
       F_e[j] = F_m[j] * epsilon_adv[j];
    }
    for(double j = 2; j <= N+2; j++){
        F_I[j] = 0.5 * (F_m[j] + F_m[j+1]) * u_adv[j];
     }
    F.push_back(F_m);
    F.push_back(F_I);
    F.push_back(F_e);
    return F;
}

vector<vector<double>> Functions::solve_shocktube(vector<double> rho, vector<double> u, vector<double> epsilon, vector<double> p, double N, double dt, double dx, double t_max, double gamma){
    double t = 0.0;
    vector<vector<double>> result;
    vector<double> sigma_vec;
    while (t < t_max){
        vector<double> rho_mean(N+4,0.0);
        vector<double> rho_mean_new(N+5,0.0);
        vector<double> rho_new = rho;
        vector<double> u_new = u;
        vector<double> epsilon_new = epsilon;
        vector<double> p_new = p;

        // Berechnung der maximalen Courantzahl für jeden Zeitschritt
        // mit Berücksichtigung der Schallgeschwindigkeit
       
        vector<double> counter(N+4,0.0);
        for(int j = 0; j < N+4; j++){
            counter[j] = sqrt(gamma * p[j] / rho[j]);
            double counter_max =  *std::max_element(counter.begin(), counter.end());
            auto u_minmax = std::minmax_element(u.begin(), u.end());
            double u_max = 0;
            if(abs(*u_minmax.first) > abs(*u_minmax.second)){
                u_max = *u_minmax.first;
            }
            else{
                u_max = *u_minmax.second;
            }
            double c_max = counter_max + u_max;
            double sigma = c_max * dt/dx;
            sigma_vec.push_back(sigma);
        }
       
        // Berechnung der Flüsse
        vector<vector<double>> F = calc_F(rho, u, epsilon, N, dt, dx);
        // F = [F_m, F_I, F_e]
        //Advektionsschritt
        for(int j = 2; j<= N+2; j++){
            rho_new[j] = rho[j] - (dt/dx) * (F[0][j+1] - F[0][j]);
        }
        for(int j = 3; j<= N+2; j++){
            rho_mean[j] = 0.5 * (rho[j-1] + rho[j]);
            rho_mean_new[j] = 0.5 * (rho_new[j-1] + rho_new[j]);
            u_new[j] = (u[j] * rho_mean[j] - dt/dx * (F[1][j] - F[1][j-1])) / rho_mean_new[j];
        }
        for(int j = 2; j<= N+2; j++){
            epsilon_new[j] = (epsilon[j] * rho[j] - dt/dx * (F[2][j+1] - F[2][j])) / rho_new[j];
        }

        // Reflektierende Randbedingungen
        u_new[2] = 0;
        u_new[1] = -u_new[3];
        u_new[N+2] = 0;
        u_new[N+3] = -u_new[N+1];
        rho_new[1] = rho_new[2];
        rho_new[0] = rho_new[3];
        rho_new[N+2] = rho_new[N+1];
        rho_new[N+3] = rho_new[N];
        epsilon_new[1] = epsilon_new[2];
        epsilon_new[0] = epsilon_new[3];
        epsilon_new[N+2] = epsilon_new[N+1];
        epsilon_new[N+3] = epsilon_new[N];

        // Druckarbeit

        for(int j = 0; j < N+4; j++){
            p_new[j] = (gamma - 1) * rho_new[j] * epsilon_new[j];
        }
        vector<double> utmp = u_new;
        for(int j = 3; j <= N+2; j++){
            u_new[j] = u_new[j] - dt/dx * (p_new[j] - p_new[j-1]) / rho_mean_new[j];
        }
        for(int j = 2; j <= N+2; j++){
            epsilon_new[j] = epsilon_new[j] - dt/dx * p_new[j]/rho_new[j] * (utmp[j+1] - utmp[j]);
        }
        rho = rho_new;
        u = u_new;
        epsilon = epsilon_new;
        p = p_new;
        t += dt;
    }
    vector<double> sigma_max_vec = {*std::max_element(sigma_vec.begin(), sigma_vec.end())};
    result.push_back(rho);
    result.push_back(u);
    result.push_back(epsilon);
    result.push_back(p);
    result.push_back(sigma_max_vec);
    return result;
}

void Functions::print_vector(vector<double> &vec){
    for(vector<double>::size_type i = 0; i < vec.size(); i++){
        std::cout << vec[i] << std::endl;
    }
}
