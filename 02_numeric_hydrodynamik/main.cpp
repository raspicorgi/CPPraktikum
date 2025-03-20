#include "lib/Functions.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h> 
#include <chrono>
#include <thread>
#include <string>
#include <cstring>
using std::string;

//Parameters
double a = 1.0;
double N = 40.0;
double x_min = -1.0;
double x_max = 1.0;
double dx = (x_max - x_min)/N;
double sigma = 0.8;
double dt = sigma*dx/a;
double t_max = 4.0;

void write_to_file(vector<double> vec, string filename){
    std::ofstream file(filename);
    for(vector<double>::size_type i = 0; i < vec.size(); i++){
        file << vec[i] << ";";
    }
    file.close();
}

int main(){
// Geister Zellen
vector<double> psi(N+4,0.0);
vector<double> u(N+5,1.0);
// Zell ränder
vector<double> x_a(N+4,0.0);
for(int i = 0; i < N+1; i++){
   x_a[i+2] = x_min + (i)*dx;
}
// Zell mitten 
vector<double> x_b(N+4,0.0);
for(int i = 0; i < N; i++){
   x_b[i+2] = x_min + 0.5*dx + i*dx;
}
// Rechteckimpuls
for(int j = 2; j < N+2 ; j++){
    if(abs(x_b[j]) <= 0.33333){
        psi[j] = 1.0;
    }
    else{
        psi[j] = 0.0;
    }
    
}
auto start = std::chrono::high_resolution_clock::now();

for(double t = 0.0; t < t_max; t+=dt){
    psi = Functions::advection(psi, N, dt, dx, u);
}

auto end = std::chrono::high_resolution_clock::now();
std::chrono::duration<double, std::milli> float_ms = end - start;
std::cout << "Laufzeit: " << float_ms.count() << " ms\n";
write_to_file(psi, "output/psi_t4_N40.txt");
write_to_file(x_b, "output/x_b.txt");
write_to_file(x_a, "output/x_a.txt");
return 0;
}