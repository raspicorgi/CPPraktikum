#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
using std::vector;

class Functions{
    public:
        static vector<double> advection(vector<double> psi, double N , double dt, double dx, vector<double> u, double t_max);
        static vector<double> rho_advection(vector<double> rho, double N , double dt, double dx, vector<double> u);
        static vector<double> u_advection(vector<double> u, double N , double dt, double dx);
        static vector<double> epsilon_advection(vector<double> epsilon, double N , double dt, double dx, vector<double> u);
        static vector<vector<double>> calc_F(vector<double> rho, vector<double> u, vector<double> epsilon, double N, double dt, double dx);
        static vector<vector<double>> solve_shocktube(vector<double> rho, vector<double> u, vector<double> epsilon, vector<double> p, double N, double dt, double dx, double t_max , double gamma);
        static double calc_delta_rho(vector<double> rho, double N, int j);
        static double calc_delta_u(vector<double> u, double N, int j);
        static double calc_delta_epsilon(vector <double> epsilon, double N, int j);
        static void print_vector(vector<double> &vec);


    private:

};

#endif // FUNCTIONS_HPP
