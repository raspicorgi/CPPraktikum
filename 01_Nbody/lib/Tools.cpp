#include <iostream>
#include "Tools.hpp"
#include <vector>
#include "Body.cpp"
#include <cmath>


    std::vector<double> Tools::calc_acceleration(std::vector<Body> bodies, Body current_body){
        std::vector<double> accelaration;
        double a_x = 0;
        double a_y = 0;
        double a_z = 0;
        for(Body other_body : bodies){
            if(other_body.is_equal(current_body)){
                continue;
            }
            double dx = other_body.getX() - current_body.getX();
            double dy = other_body.getY() - current_body.getY();
            double dz = other_body.getZ() - current_body.getZ();
            a_x = a_x + G * other_body.getMass() * (dx)/(pow(abs(dx),3));
            a_y = a_y + G * other_body.getMass() * (dy)/(pow(abs(dy),3));
            a_z = a_z + G * other_body.getMass() * (dz)/(pow(abs(dz),3));
        }
        accelaration.push_back(a_x);
        accelaration.push_back(a_y);
        accelaration.push_back(a_z);
        return accelaration;
    }

    Vector3d Tools::calc_acceleration_3dvec(std::vector<Body> bodies, Body current_body){
        Vector3d acceleration;
        for(Body other_body : bodies){
            if(other_body.is_equal(current_body)){
                continue;
            }
            Vector3d r = other_body.getPosition() - current_body.getPosition();
            acceleration = acceleration + (r * (G * other_body.getMass()) / (pow(r.magnitude(), 3)));
        }
        
        return acceleration;
    }

    std::vector<double> Tools::calc_jerk(std::vector<Body> bodies, Body current_body){
        std::vector<double> jerk;
        double j_x = 0;
        double j_y = 0;
        double j_z = 0;
        for(Body other_body : bodies){
            if(other_body.is_equal(current_body)){
                continue;
            }
            double dvx = other_body.getVx() - current_body.getVx();
            double dvy = other_body.getVy() - current_body.getVy();
            double dvz = other_body.getVz() - current_body.getVz();
            double dx = other_body.getX() - current_body.getX();
            double dy = other_body.getY() - current_body.getY();
            double dz = other_body.getZ() - current_body.getZ();
            j_x = j_x + G * other_body.getMass() * ((dvx/pow(abs(dx),3)) - (((3*(dvx*dx))/(pow(abs(dx),5)))*dx));
            j_y = j_y + G * other_body.getMass() * ((dvy/pow(abs(dy),3)) - (((3*(dvy*dy))/(pow(abs(dy),5)))*dy));
            j_z = j_z + G * other_body.getMass() * ((dvz/pow(abs(dz),3)) - (((3*(dvz*dz))/(pow(abs(dz),5)))*dz));
        }
        jerk.push_back(j_x);
        jerk.push_back(j_y);
        jerk.push_back(j_z);
        return jerk;
    }

    Vector3d Tools::calc_jerk_3dvec(std::vector<Body> bodies, Body current_body){
        Vector3d jerk;
        for(Body other_body : bodies){
            if(other_body.is_equal(current_body)){
                continue;
            }
            Vector3d r = other_body.getPosition() - current_body.getPosition();
            Vector3d v = other_body.getVelocity() - current_body.getVelocity();
            jerk = jerk + (r * (G * other_body.getMass()) / (pow(r.magnitude(), 3))) - (v * (3 * G * other_body.getMass()) * (r.scalar_product(v)) / (pow(r.magnitude(), 5)));
        }
        return jerk;
    }
