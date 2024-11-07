#include "RK4.hpp"

std::vector<Body> RK4::integrate(const std::vector<Body>& Bodies, const long double maxTimeStep){
    std::vector<Body> new_Bodies;
    std::vector<Vector3d> k1_v;
    std::vector<Vector3d> k1_r;
    std::vector<Vector3d> k2_v;
    std::vector<Vector3d> k2_r;
    std::vector<Vector3d> k3_v;
    std::vector<Vector3d> k3_r;
    std::vector<Vector3d> k4_v;
    std::vector<Vector3d> k4_r; 
    std::vector<Body> k1_bodies;
    std::vector<Body> k2_bodies;
    std::vector<Body> k3_bodies;
    for(const Body& current_body : Bodies){
        Body k1_body = current_body;
        Vector3d k1v= Tools::calc_acceleration(Bodies, current_body) * maxTimeStep;
        Vector3d k1r= current_body.getVelocity() * maxTimeStep;
        k1_v.push_back(k1v);
        k1_r.push_back(k1r);
        k1_body.setVelocity(current_body.getVelocity() + k1v*0.5);
        k1_body.setPosition(current_body.getPosition() + k1r*0.5);
        k1_bodies.push_back(k1_body);
    }
    for(const Body& current_body : Bodies){
        Body k2_body = current_body;
        Vector3d k2v = Tools::calc_acceleration(k1_bodies, k1_bodies[current_body.getId()]) * maxTimeStep;
        Vector3d k2r = (current_body.getVelocity() + k1_v[current_body.getId()]*0.5) * maxTimeStep;
        k2_v.push_back(k2v);
        k2_r.push_back(k2r);
        k2_body.setVelocity(current_body.getVelocity() + k2v*0.5);
        k2_body.setPosition(current_body.getPosition() + k2r*0.5);
        k2_bodies.push_back(k2_body);
    }
    for(const Body& current_body : Bodies){
        Body k3_body = current_body;
        Vector3d k3v = Tools::calc_acceleration(k2_bodies, k2_bodies[current_body.getId()]) * maxTimeStep;
        Vector3d k3r = (current_body.getVelocity() + k2_v[current_body.getId()]*0.5) * maxTimeStep;
        k3_v.push_back(k3v);
        k3_r.push_back(k3r);
        k3_body.setVelocity(current_body.getVelocity() + k3v);
        k3_body.setPosition(current_body.getPosition() + k3r);
        k3_bodies.push_back(k3_body);
    }
    for(const Body& current_body : Bodies){
        Vector3d k4v = Tools::calc_acceleration(k3_bodies, k3_bodies[current_body.getId()]) * maxTimeStep;
        Vector3d k4r = (current_body.getVelocity() + k3_v[current_body.getId()]) * maxTimeStep;
        k4_v.push_back(k4v);
        k4_r.push_back(k4r);
    }
    for(const Body& current_body : Bodies){
        Body new_body = current_body;
        new_body.setVelocity(current_body.getVelocity() + k1_v[current_body.getId()]/6 + k2_v[current_body.getId()]/3 + k3_v[current_body.getId()]/3 + k4_v[current_body.getId()]/6);
        new_body.setPosition(current_body.getPosition() + k1_r[current_body.getId()]/6 + k2_r[current_body.getId()]/3 + k3_r[current_body.getId()]/3 + k4_r[current_body.getId()]/6); 
        new_Bodies.push_back(new_body);
    }
    return new_Bodies;
}