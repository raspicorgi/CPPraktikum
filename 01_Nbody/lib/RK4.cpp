#include "RK4.hpp"

std::vector<Body> RK4::integrate(const std::vector<Body>& Bodies, const long double maxTimeStep){
    std::vector<Body> new_Bodies;
    std::unordered_map<int, Body> k1_map; 
    std::unordered_map<int, Body> k2_map; 
    std::unordered_map<int, Body> k3_map; 
    std::unordered_map<int, Body> k4_map; 
    for(const Body& current_body : Bodies){
        Body k1_body = current_body;
        Vector3d k1v= Tools::calc_acceleration(Bodies, current_body) * maxTimeStep;
        Vector3d k1r= current_body.getVelocity() * maxTimeStep;
        k1_body.setVelocity(k1v);
        k1_body.setPosition(k1r);
        k1_map[current_body.getId()] = k1_body;
    }
    for(const Body& current_body : Bodies){}
    for(const Body& current_body : Bodies){}
    for(const Body& current_body : Bodies){}
    for(const Body& current_body : Bodies){}

    for(const Body& current_body : Bodies){
        Body new_current_body = current_body;
        Vector3d k1v = Tools::calc_acceleration(Bodies, current_body) * maxTimeStep;
        Vector3d k1r = current_body.getVelocity() * maxTimeStep;
        new_current_body.setVelocity(current_body.getVelocity() + k1v / 2);

        Vector3d k2v = Tools::calc_acceleration(Bodies,new_current_body)* maxTimeStep;
        Vector3d k2r = (current_body.getVelocity() + k1v * 0.5)*maxTimeStep;
        new_current_body.setVelocity(current_body.getVelocity() + k2v / 2);

        Vector3d k3v = Tools::calc_acceleration(Bodies,new_current_body)* maxTimeStep;
        Vector3d k3r = (current_body.getVelocity() + k2v * 0.5)*maxTimeStep;
        new_current_body.setVelocity(current_body.getVelocity() + k3v);
        
        Vector3d k4v = Tools::calc_acceleration(Bodies,new_current_body)* maxTimeStep;
        Vector3d k4r = (current_body.getVelocity() + k3v)*maxTimeStep;
        new_current_body.setVelocity(current_body.getVelocity() + (k1v + k2v*2 + k3v*2 + k4v)*maxTimeStep / 6);
        new_current_body.setPosition(current_body.getPosition() + (k1r + k2r*2 + k3r*2 + k4r)*maxTimeStep / 6);
        new_Bodies.push_back(new_current_body);
    }
    return new_Bodies;
}