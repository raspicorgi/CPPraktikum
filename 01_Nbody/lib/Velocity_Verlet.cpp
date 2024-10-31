#include "Integrator.hpp"
#include "Tools.cpp"

class Velocity_Verlet : public Integrator{
    public:
        std::vector<Body> integrate(const std::vector<Body>* bodies, const double maxTimeStep) override {
            std::vector<Body> new_bodies;
            for(Body current_body : *bodies){
                Body new_current_body = current_body;
                std::vector<double> acceleration = Tools::calc_acceleration(*bodies,current_body);
                new_current_body.setX(current_body.getX() + current_body.getVx() * maxTimeStep + 0.5 * acceleration[0]*pow(maxTimeStep,2));
                new_current_body.setY(current_body.getY() + current_body.getVy() * maxTimeStep + 0.5 * acceleration[1]*pow(maxTimeStep,2));
                new_current_body.setZ(current_body.getZ() + current_body.getVz() * maxTimeStep + 0.5 * acceleration[2]*pow(maxTimeStep,2));
                std::vector<double> new_acceleration = Tools::calc_acceleration(*bodies,new_current_body);
                new_current_body.setVx(current_body.getVx() + 0.5*(acceleration[0]+new_acceleration[0])*maxTimeStep);
                new_current_body.setVy(current_body.getVy() + 0.5*(acceleration[1]+new_acceleration[1])*maxTimeStep);
                new_current_body.setVz(current_body.getVz() + 0.5*(acceleration[2]+new_acceleration[2])*maxTimeStep);
                new_bodies.push_back(new_current_body);
            } 
            return new_bodies;
        }
};