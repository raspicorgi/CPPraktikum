#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <vector>
#include <iostream>
using std::vector;

class Functions{
    public:
        static vector<double> advection(vector <double> &psi, int N , double dt, double dx, vector <double> u);
        static double calc_delta_psi(vector <double> &psi, int N, int j);
        static void print_vector(vector<double> &vec);
    private:

};

#endif // FUNCTIONS_HPP
