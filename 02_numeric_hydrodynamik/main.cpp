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



// Funktion um die Precision der doubles für die Ausgabe zu verringern 
std::string double_to_string(double &variable)
{
   std::ostringstream Str;
   Str.precision(3);
   Str <<std::fixed<< variable;
   return(Str.str());
}

void write_to_file(vector<double> vec, string filename){
    std::ofstream file(filename);
    for(vector<double>::size_type i = 0; i < vec.size(); i++){
        if(i == vec.size()-1){
            file << vec[i];
            break;

        }
        else{
        file << vec[i] << ";";
        }
    }
    file.close();
}

int main(){
std::cout<<"Numerische Hydrodynamik, welche aufgabe möchten sie Lösen?"<<std::endl;
int choice = 0;
std::cin>>choice;
if(choice == 1){
//Parameters
double a = 1.0;
double N = 40.0;
double x_min = -1.0;
double x_max = 1.0;
double sigma = 0.9;
double t_max = 4.0;

// std::cout<<"Bitte geschwindigkeit a eingeben: "<<std::endl;
// std::cin>>a;
// std::cout<<"Bitte Anzahl der Zellen N eingeben: "<<std::endl;
// std::cin>>N;
// std::cout<<"Bitte x_min eingeben: "<<std::endl;
// std::cin>>x_min;
// std::cout<<"Bitte x_max eingeben: "<<std::endl;
// std::cin>>x_max;
// std::cout<<"Bitte sigma eingeben: "<<std::endl;
// std::cin>>sigma;
// std::cout<<"Bitte t_max eingeben: "<<std::endl;
// std::cin>>t_max;


double dx = (x_max - x_min)/N;
double dt = sigma*dx/a;

// Geister Zellen
vector<double> psi(N+4,0.0); // Psi läuft von 0 bis N+3 also insgemsamt N+4 Elemente
vector<double> u(N+4,0.0);
// Zell ränder
vector<double> x_a(N+4,0.0);
for(int i = 0; i <= N; i++){
   x_a[i+2] = x_min + (i)*dx;
}
// Zell mitten 
vector<double> x_b(N+4,0.0);
for(int i = 0; i < N; i++){
   x_b[i+2] = x_min + 0.5*dx + i*dx;
}
// Rechteckimpuls
for(int j = 2; j <= N+2 ; j++){
    if(abs(x_b[j]) <= 0.333333333333333333){
        psi[j] = 1.0;
    }
    else{
        psi[j] = 0.0;
    }
    
}
// Geschwindigkeit
for(int j = 2; j <= N+2; j++){
    u[j] = a;
}

auto start = std::chrono::high_resolution_clock::now();
vector<double> psi_new(N+4,0.0);
psi_new = Functions::advection(psi, N, dt, dx, u, t_max);


auto end = std::chrono::high_resolution_clock::now();
std::chrono::duration<double, std::milli> float_ms = end - start;
std::cout << "Laufzeit: " << float_ms.count() << " ms\n";
write_to_file(psi_new, "output/psi_t"+ double_to_string(t_max)+"s_N"+double_to_string(N)+"_sigma"+double_to_string(sigma) +".txt");
write_to_file(x_b, "output/xb_t"+double_to_string(t_max)+"_N"+ double_to_string(N) +"_sigma"+ double_to_string(sigma) +".txt");
write_to_file(x_b, "output/xa_t"+double_to_string(t_max)+"_N"+ double_to_string(N) +"_sigma"+ double_to_string(sigma) +".txt");
return 0;
}
else if(choice == 2){
//Parameters
double x_min = 0.0;
double x_max = 1.0;
double gamma = 1.4;
double N = 100;
double t_max = 0.228;
double dt = 0.001;
double dx = (x_max - x_min) / N;
 // geisterzellen
vector<double> rho(N+4,0.0);
vector<double> u(N+4,0.0);
vector<double> epsilon(N+4,0.0);
vector<double> p(N+4,0.0);
vector<double> xb(N+4,0.0);
vector<double> xa(N+4,0.0);
// Zell ränder
for(int i = 0; i <= N; i++){
   xa[i+2] = x_min + (i)*dx;
}
// Zell mitten 
for(int i = 0; i < N; i++){
   xb[i+2] = x_min + 0.5*dx + i*dx;
}
//anfangsbedingungen
 for(int j = 0; j < N+4; j++){
     if(xb[j] <= 0.5){
         rho[j] = 1.0;
         u[j] = 0.0;
         p[j] = 1.0;
         epsilon[j] = 2.5;
     }
     else{
         rho[j] = 0.125;
         u[j] = 0.0;
         p[j] = 0.1;
         epsilon[j] = 2.0;
     }
 }

vector<vector<double>> result = Functions::solve_shocktube(rho, u, epsilon, p, N, dt, dx, t_max, gamma);
// result = [rho, u, epsilon, p, sigma_max_vec]
vector<double> temp(N+4);
for(int j = 0; j < N+4; j++){
    temp[j] = result[2][j] * (gamma -1);
}
write_to_file(result[0], "output_a2/rho_t"+ double_to_string(t_max)+"s_N"+double_to_string(N)+"_dt"+double_to_string(dt) +".txt");
write_to_file(result[1], "output_a2/u_t"+ double_to_string(t_max)+"s_N"+double_to_string(N)+"_dt"+double_to_string(dt) +".txt");
write_to_file(result[2], "output_a2/epsilon_t"+ double_to_string(t_max)+"s_N"+double_to_string(N)+"_dt"+double_to_string(dt) +".txt");
write_to_file(result[3], "output_a2/p_t"+ double_to_string(t_max)+"s_N"+double_to_string(N)+"_dt"+double_to_string(dt) +".txt");
write_to_file(result[4], "output_a2/sigma_max"+ double_to_string(t_max)+"s_N"+double_to_string(N)+"_dt"+double_to_string(dt) +".txt");
write_to_file(temp, "output_a2/T_t"+ double_to_string(t_max)+"s_N"+double_to_string(N)+"_dt"+double_to_string(dt) +".txt");
write_to_file(xb, "output_a2/xb_t"+ double_to_string(t_max)+"s_N"+double_to_string(N)+"_dt"+double_to_string(dt) +".txt");

return 0;
}
else{
    std::cout<<"Ungültige Eingabe"<<std::endl;
    return 0;
}
}