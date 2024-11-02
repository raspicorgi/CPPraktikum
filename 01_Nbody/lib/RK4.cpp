#include "RK4.hpp"

std::vector<Body> RK4::integrate(const std::vector<Body>& Bodies, const double maxTimeStep){
    std::vector<Body> new_Bodies;
    for(const Body& current_body : Bodies){
        Body new_current_body = current_body;
        Vector3d k1v = Tools::calc_acceleration(Bodies, current_body) * maxTimeStep;
        Vector3d k1r = current_body.getVelocity() * maxTimeStep;
        new_current_body.setPosition(current_body.getPosition() + k1r / 2);
        Vector3d k2v = Tools::calc_acceleration(Bodies,new_current_body)* maxTimeStep;
        Vector3d k2r = (current_body.getVelocity() + k1v * 0.5)*maxTimeStep;
        new_current_body.setPosition(current_body.getPosition() + k2r / 2);
        Vector3d k3v = Tools::calc_acceleration(Bodies,new_current_body)* maxTimeStep;
        Vector3d k3r = (current_body.getVelocity() + k2v * 0.5)*maxTimeStep;
        new_current_body.setPosition(current_body.getPosition() + k3r);
        Vector3d k4v = Tools::calc_acceleration(Bodies,new_current_body)* maxTimeStep;
        Vector3d k4r = (current_body.getVelocity() + k3v)*maxTimeStep;
        new_current_body.setVelocity(current_body.getVelocity() + (k1v + k2v*2 + k3v*6 + k4v) / 6);
        new_current_body.setPosition(current_body.getPosition() + (k1r + k2r*2 + k3r*6 + k4r) / 6);
        new_Bodies.push_back(new_current_body);
    }
    return new_Bodies;
}